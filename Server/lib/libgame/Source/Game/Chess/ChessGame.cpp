#include "ChessGame.h"
#include <MsgMgr.h>
#include <ConfigService.h>
#include <Game/Chess/ChessManager.h>

using namespace std;

int Pos2ID(int posx, int posy)
{
	return (posy - 1) * 8 + posx;
}

bool ChessGame::Init()
{
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

		m_Board[Pos2ID(piece.posx, piece.posy)] = piece.id;
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
	//todo:清除缓存，写出游戏记录
	return true;
}

void ChessGame::onMsg_Chess_Action_C2S(const Msg_Chess_Action_C2S& msg)
{
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
		for (int i = 0; i <= 1; i++)
		{
			Msg_Chess_Regret_S2C msg;
			auto&& lastStep = m_RecordsMap[--m_turn_id];
			for (auto&& piece : lastStep.pieces())
			{
				auto&& copy = msg.add_pieces();
				copy->set_id(piece.id());
				copy->set_ori_posx(piece.ori_posx());
				copy->set_ori_posx(piece.ori_posx());
				copy->set_des_posx(piece.des_posx());
				copy->set_des_posx(piece.des_posx());
			}
			SendToPlayers(msg);
		}
	}
}

void ChessGame::onMsg_Chess_Pause_C2S(const Msg_Chess_Pause_C2S& msg)
{
}

bool ChessGame::ckeckActionAble(int id, int x, int y)
{
	if (x < 1 || x>8 || y < 1 || y>8)return false;

	auto& piece = m_Pieces[id];
	int targetPosId = Pos2ID(x, y);
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
		if (
			(abs(piece.posx - x) != 0) &&
			(abs(piece.posy - y) != 0) &&
			(abs(piece.posx - x) != abs(piece.posy - y))
			)return false;////王后能够直线和斜线移动
		if (m_Board[targetPosId] != 0)
		{
			auto&& targetPiece = m_Pieces[m_Board[targetPosId]];
			if (piece.color == targetPiece.color)return false;//无法攻击友方棋子
		}
	}
	break;
	case MsgPB::Car:
	{
		if (
			(abs(piece.posx - x) != 0) &&
			(abs(piece.posy - y) != 0)
			)return false;////车能够直线移动
		if (m_Board[targetPosId] != 0)
		{
			auto&& targetPiece = m_Pieces[m_Board[targetPosId]];
			if (piece.color == targetPiece.color)return false;//无法攻击友方棋子
		}
	}
	break;
	case MsgPB::Elephant:
	{
		if (
			abs(piece.posx - x) != abs(piece.posy - y)
			)return false;//象能够斜线移动
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
			if (m_Board[targetPosId] != 0)
			{
				auto&& targetPiece = m_Pieces[m_Board[targetPosId]];
				if (piece.color != targetPiece.color)return true;
			}
		}
		//第一次前进
		if (piece.color == White)
		{
			legealy += 1;
		}
		else if (piece.color == Black)
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
	{
		p->set_id(piece.id);
		p->set_des_posx(piece.posx);
		p->set_des_posy(piece.posy);
	}
	m_Board[Pos2ID(x, y)] = piece.id;

	//发送消息
	m_RecordsMap.emplace(++m_turn_id, msg);
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
