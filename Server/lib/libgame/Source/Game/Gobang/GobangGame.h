#pragma once
#include <iostream>
#include <Game/Game.h>
#include "ClientUser.h"
#include "../lib/libmsg/source/msg/Msg.pb.h"

#define CoordID(x,y) (((x) * 19) + (y))

struct GobangAction
{
	int role;
	int x;
	int y;
};

class GobangGame :public Game
{
public:
	GobangGame(ClientUser* user1, ClientUser* user2, int GameId)
		:m_User1(user1), m_User2(user2), m_GameId(GameId)
	{
		if (user1 && user2)
		{
			user1->joinGobang(this);
			user2->joinGobang(this);
			Init();
			Start();
		}
	}

	~GobangGame()
	{
		Shut();
	}
public:
	bool Init()override;
	bool Start()override;
	bool Shut()override;
public:
	void onMsg_Gobang_Action_C2S(const Msg_Gobang_Action_C2S& msg);
	void onMsg_Gobang_Giveup_C2S(const Msg_Gobang_Giveup_C2S& msg);
	void onMsg_Gobang_Regret_C2S(const Msg_Gobang_Regret_C2S& msg);
	void onMsg_Gobang_Pause_C2S(const Msg_Gobang_Pause_C2S& msg);

	bool ckeckGameOver(int x, int y);

	MsgPB::COLOR getPiece(int x, int y);

	template<class MsgT>
	inline void SendToPlayers(const MsgT& msg)
	{
		m_User1->getMsgMgr()->SendMsg(msg);
		m_User2->getMsgMgr()->SendMsg(msg);
	}
private:
	ClientUser* m_User1;
	ClientUser* m_User2;
	int m_CurrentTurn{};
	int m_GameId{};
	std::map<int, MsgPB::COLOR> m_State{};
	std::map<int/*turn_Id*/, GobangAction> m_RecordsMap{};
};