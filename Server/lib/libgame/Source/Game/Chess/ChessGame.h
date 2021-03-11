#pragma once
#include <iostream>
#include <Game/Game.h>
#include "ClientUser.h"
#include "../lib/libmsg/source/msg/Msg.pb.h"

#define CoordID(x,y) (((x) * 19) + (y))

class ChessGame :public Game
{
public:
	ChessGame(ClientUser* user1, ClientUser* user2, int GameId)
		:m_User1(user1), m_User2(user2), m_GameId(GameId)
	{
		if (user1 && user2)
		{
			user1->joinChess(this);
			user2->joinChess(this);
			Init();
			Start();
		}
	}

	~ChessGame()
	{
		Shut();
	}
private:
	void Init();
	void Start();
	void Update();
	void Shut();
public:
	void onMsg_Chess_Action_C2S(const Msg_Chess_Action_C2S& msg);
	bool ckeckGameOver(int x, int y);

	template<class MsgT>
	inline void SendToPlayers(const MsgT& msg)
	{
		m_User1->getMsgMgr()->SendMsg(msg);
		m_User2->getMsgMgr()->SendMsg(msg);
	}
private:
	ClientUser* m_User1;
	ClientUser* m_User2;
	int m_GameId{};
	std::map<int, MsgPB::CHESSTYPE> m_State{};
};