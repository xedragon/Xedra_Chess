#pragma once
#include <tuple>
#include <iostream>
#include <Game/Game.h>
#include <Game/Chess/ChessPiece.h>
#include "ClientUser.h"
#include "../lib/libmsg/source/msg/Msg.pb.h"


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
public:
	bool Init()override;
	bool Start()override;
	bool Shut()override;
public:
	void onMsg_Chess_Action_C2S(const Msg_Chess_Action_C2S& msg);
	void onMsg_Chess_Giveup_C2S(const Msg_Chess_Giveup_C2S& msg);
	void onMsg_Chess_Regret_C2S(const Msg_Chess_Regret_C2S& msg);
	void onMsg_Chess_Pause_C2S(const Msg_Chess_Pause_C2S& msg);

	bool ckeckGameOver();
	bool ckeckActionAble(int id, int x, int y);
	void Action(int id, int x, int y);
	inline int getGameID()
	{
		return m_GameId;
	}

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
	std::map<int, ChessPiece> m_Pieces{};
	std::map<int/*pos*/, int/*piece id*/> m_Board{};

	int m_turn_id{};
	std::map<int/*turnId*/, Msg_Chess_Action_S2C> m_RecordsMap{};
};