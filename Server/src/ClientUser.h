#pragma once
#include <iostream>
#include <MsgMgr.h>
#include <libmsg/source/msg/Msg.pb.h>
#include <WinSock2.h>
#define MSGHEADLEN 4

class ClientUser//:public MsgHandler
{
public:
	ClientUser(SOCKET socket);
public:
	bool Init();
	bool Update();
	bool Shut();
private:
	void PushMsg(char* szMsg, int nLen);
	void LogError(DWORD error);
	void SendMsg(char* pMsg, int len);
private:
	void onLogin(Msg_Login_C2S msg);
private:
	SOCKET _socket{};
	char m_RecvBuf[1024];
	char m_SendBuf[1024];
	int m_RecvBufLen{};
	int m_SendBufLen{};
};