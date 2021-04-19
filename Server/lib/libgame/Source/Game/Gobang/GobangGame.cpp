#include "GobangGame.h"
#include <MsgMgr.h>
#include <Game/Gobang/GobangManager.h>

using namespace std;

bool GobangGame::Init()
{
	return true;
}

bool GobangGame::Start()
{
	MsgPB::Msg_Gobang_Start_S2C msg;
	msg.set_gameid(m_GameId);

	msg.set_role(MsgPB::COLOR::White);
	m_User1->getMsgMgr()->SendMsg(msg);
	msg.set_role(MsgPB::COLOR::Black);
	m_User2->getMsgMgr()->SendMsg(msg);

	return true;
}

bool GobangGame::Shut()
{
	m_User1->exitGobang();
	m_User2->exitGobang();
	//todo:写出游戏记录
	return true;
}

void GobangGame::onMsg_Gobang_Action_C2S(const Msg_Gobang_Action_C2S& msg)
{
	int coord = CoordID(msg.x(), msg.y());

	if (coord<(-9 * 19 - 9) || coord>(9 * 19 + 9))
	{
		//位置越界
		return;
	}
	else if (m_State[coord] != COLOR::Null)
	{
		//该位置已有棋子
		return;
	}
	else
	{
		//有效棋步
		m_State[coord] = msg.role();

		//游戏记录
		m_RecordsMap.emplace(++m_CurrentTurn, GobangAction{ msg.role(),msg.x(),msg.y() });

		//回复消息
		Msg_Gobang_Action_C2S reply(msg);
		reply.set_turnid(m_CurrentTurn);
		//m_User1->getMsgMgr()->SendMsg(msg);
		SendToPlayers(reply);
	}

	//检测游戏结束
	if (ckeckGameOver(msg.x(), msg.y()))
	{
		Msg_Gobang_Over_S2C overmsg;
		overmsg.set_winner(getPiece(msg.x(), msg.y()));
		SendToPlayers(overmsg);

		GobangManager::getInstance().ShutGame(m_GameId);
	}
}

void GobangGame::onMsg_Gobang_Giveup_C2S(const Msg_Gobang_Giveup_C2S& msg)
{
	Msg_Gobang_Giveup_S2C reply;
	SendToPlayers(reply);
}

void GobangGame::onMsg_Gobang_Regret_C2S(const Msg_Gobang_Regret_C2S& msg)
{
}

void GobangGame::onMsg_Gobang_Pause_C2S(const Msg_Gobang_Pause_C2S& msg)
{
	Msg_Gobang_Pause_S2C reply;
	SendToPlayers(reply);
}

bool GobangGame::ckeckGameOver(int x, int y)
{
	const auto& here = getPiece(x, y);
	if (here == MsgPB::COLOR::Null)return false;
	//ckeck x
	{
		int tx = x;
		int ty = y;
		int count = 0;
		while (getPiece(tx, ty) == here)
		{
			count++;
			tx++;
		}
		tx = x;
		while (getPiece(tx, ty) == here)
		{
			count++;
			tx--;
		}
		if (count > 5)return true;
	}
	//ckeck y
	{
		int tx = x;
		int ty = y;
		int count = 0;
		while (getPiece(tx, ty) == here)
		{
			count++;
			ty++;
		}
		tx = x;
		while (getPiece(tx, ty) == here)
		{
			count++;
			ty--;
		}
		if (count > 5)return true;
	}
	//ckeck oblique "/"
	{
		int tx = x;
		int ty = y;
		int count = 0;
		while (getPiece(tx, ty) == here)
		{
			count++;
			tx++;
			ty++;
		}
		tx = x;
		while (getPiece(tx, ty) == here)
		{
			count++;
			tx--;
			ty--;
		}
		if (count > 5)return true;
	}
	//ckeck oblique "\"
	{
		int tx = x;
		int ty = y;
		int count = 0;
		while (getPiece(tx, ty) == here)
		{
			count++;
			tx++;
			ty--;
		}
		tx = x;
		while (getPiece(tx, ty) == here)
		{
			count++;
			tx--;
			ty++;
		}
		if (count > 5)return true;
	}

	return false;
}

MsgPB::COLOR GobangGame::getPiece(int x, int y)
{
	if (abs(x) <= 9 && abs(y) <= 9)
	{
		int id = CoordID(x, y);
		auto&& itr = m_State.find(id);
		if (itr != m_State.end())
		{
			return itr->second;
		}
	}
	return MsgPB::COLOR::Null;
}
