#include "ChessGame.h"
#include <MsgMgr.h>
#include <ConfigService.h>
#include <Game/Chess/ChessManager.h>

using namespace std;

bool ChessGame::Init()
{
	m_turn_id = 0;
	//todo: Init Board
	for (int i = 1; i <= 32; i++)
	{
		auto&& pItem = ConfigService::getInstance().cfgChessTypeTableItem(i);
		if (!pItem)continue;

		auto& piece = m_Pieces[i];
		piece.id = pItem->id;
		piece.color = pItem->color;
		piece.type = pItem->type;
		piece.posx = pItem->posx;
		piece.posy = pItem->posy;
		piece.AddTrack(m_turn_id, piece.posx, piece.posy);

		m_Board[piece.Posid()] = piece.id;
	}
	return true;
}

bool ChessGame::Start()
{
	MsgPB::Msg_Chess_Start_S2C msg;
	msg.set_gameid(m_GameId);

	//todo: send startmsg
	msg.set_role(COLOR::Black);
	m_User2->getMsgMgr()->SendMsg(msg);
	msg.set_role(COLOR::White);
	m_User1->getMsgMgr()->SendMsg(msg);

	return true;
}

bool ChessGame::Shut()
{
	m_User1->exitChess();
	m_User2->exitChess();
	//通知玩家游戏关闭
	Msg_Chess_Close_S2C msg;
	SendToPlayers(msg);

	//todo:清除缓存，写出游戏记录
	return true;
}

void ChessGame::onMsg_Chess_Action_C2S(const Msg_Chess_Action_C2S& msg)
{
	/*for (auto&& piece : msg.pieces())
	{
		cout << fmt::format("onMsg_Chess_Action_C2S_Piece:id:{0},posx:{1},posy:{2}", piece.id(), piece.des_posx(), piece.des_posy()) << endl;
	}*/
	for (auto& piece : msg.pieces())
	{
		//检查操作是否合法
		if (ckeckActionAble(piece.id(), piece.des_posx(), piece.des_posy()))
		{
			//合法给予执行
			Action(piece.id(), piece.des_posx(), piece.des_posy());
			//执行后检测胜负
			if (ckeckGameOver())
			{
				ChessManager::getInstance().ShutGame(m_GameId);
			}
		}
	}
}

void ChessGame::onMsg_Chess_Giveup_C2S(const Msg_Chess_Giveup_C2S& msg)
{
	Msg_Chess_Giveup_S2C reply;
	SendToPlayers(reply);
}

void ChessGame::onMsg_Chess_Regret_C2S(const Msg_Chess_Regret_C2S& msg)
{
	if (m_RecordsMap.size() >= 2)
	{
		Msg_Chess_Regret_S2C msg;
		for (int i = 0; i <= 1; i++)
		{
			auto&& lastStep = m_RecordsMap[m_turn_id--];
			for (auto&& ritr=lastStep.pieces().rbegin();ritr!= lastStep.pieces().rend();ritr++)
			{
				auto piece = *ritr;
				//cout << fmt::format("regret: id:{0},oriposx:{1},oriposy:{2},desposx:{3},desposy:{4}\n", piece.id(), piece.ori_posx(), piece.ori_posy(), piece.des_posx(), piece.des_posy());

				auto&& datapiece = m_Pieces[piece.id()];
				m_Board[datapiece.Posid()] = 0;
				datapiece.posx = piece.ori_posx();
				datapiece.posy = piece.ori_posy();
				datapiece.PopTrack();
				m_Board[datapiece.Posid()] = datapiece.id;

				auto&& copy = msg.add_pieces();
				copy->set_id(piece.id());
				copy->set_ori_posx(piece.ori_posx());
				copy->set_ori_posy(piece.ori_posy());
				copy->set_des_posx(piece.des_posx());
				copy->set_des_posy(piece.des_posy());
			}
			m_RecordsMap.erase(m_turn_id+1);
		}
		msg.set_turnid(m_turn_id);
		SendToPlayers(msg);
	}
}

void ChessGame::onMsg_Chess_Pause_C2S(const Msg_Chess_Pause_C2S& msg)
{
}

bool ChessGame::ckeckActionAble(int id, int x, int y)
{
	if (x < 1 || x>8 || y < 1 || y>8)return false;

	auto& piece = m_Pieces[id];//操作子
	if (piece.posx == x && piece.posy == y)return false;//原位
	int targetPosId = Pos2ID(x, y);//目标子
	switch (piece.type)
	{
	case MsgPB::King:
	{
		if (abs(piece.posx - x) > 1 || abs(piece.posy - y) > 1)return false;//国王只能移动一格
		if (m_Board[targetPosId] != 0)
		{
			auto&& targetPiece = m_Pieces[m_Board[targetPosId]];
			if (piece.color == targetPiece.color)return false;//无法攻击友方棋子
		}
	}
	break;
	case MsgPB::Queen:
	{
		if (m_Board[targetPosId] != 0)
		{
			auto&& targetPiece = m_Pieces[m_Board[targetPosId]];
			if (piece.color == targetPiece.color)return false;//无法攻击友方棋子
		}

		//王后能够直线移动，但不能越子
		if (piece.posx == x)
		{
			int ty = piece.posy;
			while (ty != y)
			{
				if (ty < y)ty++;
				if (ty > y)ty--;
				if (m_Board[Pos2ID(x, ty)] != 0 && ty != y)return false;
			}
		}
		else if (piece.posy == y)
		{
			int tx = piece.posx;
			while (tx != x)
			{
				if (tx < x)tx++;
				if (tx > x)tx--;
				if (m_Board[Pos2ID(tx, y)] != 0 && tx != x)return false;
			}
		}
		else if (abs(piece.posx - x) == abs(piece.posy - y))
		{
			int tx = piece.posx;
			int ty = piece.posy;
			while (tx != x || ty != y)
			{
				if (tx < x)tx++;
				if (tx > x)tx--;
				if (ty < y)ty++;
				if (ty > y)ty--;
				if (m_Board[Pos2ID(tx, ty)] != 0 && tx != x)return false;
			}
		}
		else
		{
			return false;
		}
	}
	break;
	case MsgPB::Car:
	{
		if (m_Board[targetPosId] != 0)
		{
			auto&& targetPiece = m_Pieces[m_Board[targetPosId]];
			if (piece.color == targetPiece.color)return false;//无法攻击友方棋子
		}

		if (piece.posx == x)
		{
			int ty = piece.posy;
			while (ty != y)
			{
				if (ty < y)ty++;
				if (ty > y)ty--;
				if (m_Board[Pos2ID(x, ty)] != 0 && ty != y)return false;
			}
		}
		else if (piece.posy == y)
		{
			int tx = piece.posx;
			while (tx != x)
			{
				if (tx < x)tx++;
				if (tx > x)tx--;
				if (m_Board[Pos2ID(tx, y)] != 0 && tx != x)return false;
			}
		}
		else
		{
			return false;
		}
	}
	break;
	case MsgPB::Elephant:
	{
		//象能够斜线移动不能越子
		if (abs(piece.posx - x) == abs(piece.posy - y))
		{
			int tx = piece.posx;
			int ty = piece.posy;
			while (tx != x || ty != y)
			{
				if (tx < x)tx++;
				if (tx > x)tx--;
				if (ty < y)ty++;
				if (ty > y)ty--;
				if (m_Board[Pos2ID(tx, ty)] != 0 && tx != x)return false;
			}
		}
		else
		{
			return false;
		}

		if (m_Board[targetPosId] != 0)
		{
			auto&& targetPiece = m_Pieces[m_Board[targetPosId]];
			if (piece.color == targetPiece.color)return false;//无法攻击友方棋子
		}
	}
	break;
	case MsgPB::Horse:
	{
		if (
			abs(piece.posx - x) + abs(piece.posy - y) != 3
			)return false;//马走日
		if (m_Board[targetPosId] != 0)
		{
			auto&& targetPiece = m_Pieces[m_Board[targetPosId]];
			if (piece.color == targetPiece.color)return false;//无法攻击友方棋子
		}
	}
	break;
	case MsgPB::Solider:
	{
		int legealy = piece.posy;
		if (piece.color == White)
		{
			legealy += 1;
		}
		else if (piece.color == Black)
		{
			legealy -= 1;
		}
		//正常前进
		if (y == legealy && abs(piece.posx - x) == 0)return true;
		//过路兵
		if (y == legealy && abs(piece.posx - x) == 1)
		{
			if (m_Board[Pos2ID(piece.posx,y)] != 0)
			{
				auto&& targetPiece = m_Pieces[m_Board[Pos2ID(piece.posx, y)]];
				if (piece.color != targetPiece.color)return true;
			}
		}
		//第一次前进
		if (piece.color == White && piece.NerverMove())
		{
			legealy += 1;
		}
		else if (piece.color == Black && piece.NerverMove())
		{
			legealy -= 1;
		}
		if (y == legealy && abs(piece.posx - x) == 0)return true;
		//其他情况非法
		return false;
	}
	break;
	default:
		break;
	}

	return true;     
}

void ChessGame::Action(int id, int x, int y)
{
	//回合数递增
	m_turn_id++;

	auto&& piece = m_Pieces[id];
	Msg_Chess_Action_S2C msg;

	//原来位置
	m_Board[Pos2ID(piece.posx, piece.posy)] = 0;
	//目标位置
	if (m_Board[Pos2ID(x, y)] != 0)
	{
		auto&& targetpiece = m_Pieces[m_Board[Pos2ID(x, y)]];
		//吃掉
		if (targetpiece.color != piece.color)
		{
			auto p = msg.add_pieces();
			{
				p->set_ori_posx(targetpiece.posx);
				p->set_ori_posy(targetpiece.posy);
			}
			targetpiece.posx = 0;
			targetpiece.posy = 0;
			targetpiece.AddTrack(m_turn_id, 0, 0);
			{
				p->set_id(targetpiece.id);
				p->set_des_posx(targetpiece.posx);
				p->set_des_posy(targetpiece.posy);
			}
			m_Board[Pos2ID(x, y)] = 0;
		}
	}
	//更新位置
	auto p = msg.add_pieces();
	{
		p->set_ori_posx(piece.posx);
		p->set_ori_posy(piece.posy);
	}
	piece.posx = x;
	piece.posy = y;
	piece.AddTrack(m_turn_id, x, y);
	{
		p->set_id(piece.id);
		p->set_des_posx(piece.posx);
		p->set_des_posy(piece.posy);
	}
	m_Board[Pos2ID(x, y)] = piece.id;
	//兵的升变
	if (piece.type == CHESSTYPE::Solider)
	{
		if (piece.color == COLOR::White && piece.posy == 8)
		{
			//白兵升变
		}
		else if (piece.color == COLOR::Black && piece.posy == 1)
		{
			//黑兵升变
		}
	}


	//发送消息
	m_RecordsMap.emplace(m_turn_id, msg);
	msg.set_turnid(m_turn_id);
	SendToPlayers(msg);

}

bool ChessGame::ckeckGameOver()
{
	//todo:
	if ((m_Pieces[1].posx == 0) && (m_Pieces[1].posy == 0))
	{
		Msg_Chess_Over_S2C msg;
		msg.set_winner(COLOR::Black);
		SendToPlayers(msg);
		return true;
	}
	else if ((m_Pieces[17].posx == 0) && (m_Pieces[17].posy == 0))
	{
		Msg_Chess_Over_S2C msg;
		msg.set_winner(COLOR::White);
		SendToPlayers(msg);
		return true;
	}

	return false;
}
