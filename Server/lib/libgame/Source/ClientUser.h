#pragma once
#include <BaseUtil.h>
#include <WinSock2.h>
#include "../lib/libmsg/source/msg/Msg.pb.h"


using namespace MsgPB;
class MsgMgr;
class GobangGame;
class ChessGame;

class ClientUser// : public MsgHandler
{
public:
	ClientUser(SOCKET socket);
public:
	bool Init();
	bool Update();
	bool Shut();
public:
	MsgMgr* getMsgMgr();
	void joinGobang(GobangGame* game);
	void joinChess(ChessGame* game);
	void exitGobang();
	void exitChess();
	GobangGame* getGobangGame();
private:
	void onLogin_C2S(const Msg_Login_C2S& msg);
	void onMsg_Gobang_Match_C2S(const Msg_Gobang_Match_C2S& msg);
	void onMsg_Gobang_Action_C2S(const Msg_Gobang_Action_C2S& msg);
	void onMsg_Gobang_Giveup_C2S(const Msg_Gobang_Giveup_C2S& msg);
	void onMsg_Gobang_Regret_C2S(const Msg_Gobang_Regret_C2S& msg);
	void onMsg_Gobang_Pause_C2S(const Msg_Gobang_Pause_C2S& msg);

	void onMsg_Chess_Match_C2S(const Msg_Chess_Match_C2S& msg);
	void onMsg_Chess_Action_C2S(const Msg_Chess_Action_C2S& msg);
	void onMsg_Chess_Giveup_C2S(const Msg_Chess_Giveup_C2S& msg);
	void onMsg_Chess_Regret_C2S(const Msg_Chess_Regret_C2S& msg);
	void onMsg_Chess_Pause_C2S(const Msg_Chess_Pause_C2S& msg);
private:
	void ConenctToAccount(std::string name);
private:
	std::shared_ptr<MsgMgr> m_MsgMgr{};
	GobangGame* m_pGobangGame{};
	ChessGame* m_pChessGame{};
private:
	SOCKET _socket{};
	int _id{};
	std::string _name{};
};