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
	GobangGame* getGobangGame();
private:
	void onLogin_C2S(const Msg_Login_C2S& msg);
	void onMsg_Gobang_Match_C2S(const Msg_Gobang_Match_C2S& msg);
	void onMsg_Gobang_Action_C2S(const Msg_Gobang_Action_C2S& msg);
private:
	void ConenctToAccount(std::string name);
private:
	std::shared_ptr<MsgMgr> m_MsgMgr{};
	GobangGame* m_pGobangGame{};
	ChessGame* m_pChessGame{};
private:
	int _id{};
	std::string _name{};
};