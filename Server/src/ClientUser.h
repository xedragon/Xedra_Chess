#pragma once
#include <iostream>
#include <WinSock2.h>
#define MSGHEADLEN 4
class ClientUser
{
public:
	ClientUser(SOCKET socket);
public:
	bool Update();
	bool Shut();
private:
	void PushMsg(char* szMsg, int nLen);
	void LogError(DWORD error);
	void SendMsg(char* pMsg, int len);
private:
	SOCKET _socket{};
	char m_RecvBuf[1024];
	char m_SendBuf[1024];
	int m_RecvBufLen{};
	int m_SendBufLen{};
};