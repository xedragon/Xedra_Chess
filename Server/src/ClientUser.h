#pragma once
#include <iostream>
#include <WinSock2.h>
#include <libmsg/source/msg/Msg.pb.h>

class MsgMgr;

class ClientUser// : public MsgHandler
{
public:
	ClientUser(SOCKET socket);
public:
	bool Init();
	bool Update();
	bool Shut();

	void test();
public:
	MsgMgr* getMsgMgr();
private:
	void onLogin(const Msg_Login_C2S& msg);
private:
	std::shared_ptr<MsgMgr> m_MsgMgr{};
};