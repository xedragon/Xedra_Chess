#include "NetMoudle.h"
#include <iostream>
#include <Facade.h>
#include <ClientUser.h>
#include <ConfigService.h>
#include <automake/tableconfig.h>
using namespace std;

NetMoudle::NetMoudle()
{

}

static NetMoudle* g_NetMoudle = nullptr;
NetMoudle& NetMoudle::getInstance()
{
	if (g_NetMoudle == nullptr)
	{
		g_NetMoudle = new NetMoudle();
	}
	return *g_NetMoudle;
}

bool NetMoudle::Init()
{
	auto GloabalCfg = ConfigService::getInstance().tbsGlobalCfgItemItem();
	//初始化
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in sockaddr;
	sockaddr.sin_family = PF_INET;
	sockaddr.sin_addr.S_un.S_addr = inet_addr(GloabalCfg->ServerIP.c_str());
	sockaddr.sin_port = htons(GloabalCfg->ServerPort);

	//非阻塞模式
	int mode = 1;
	ioctlsocket(_socket, FIONBIO, (u_long*)&mode);

	//绑定端口
	bind(_socket, (const struct sockaddr*)&sockaddr, sizeof(sockaddr));
	listen(_socket, 1);

	return true;
}

bool NetMoudle::Update()
{
	Accept();

	auto itr = m_ClientUsersVec.begin();
	while (true)
	{
		if (itr == m_ClientUsersVec.end())
			break;
		if (!(*itr)->Update())
		{
			(*itr)->Shut();
			itr = m_ClientUsersVec.erase(itr);
		}

		if (itr != m_ClientUsersVec.end())
		{
			itr++;
		}
	}

	return true;
}

bool NetMoudle::Shut()
{
	return true;
}

void NetMoudle::Accept()
{
	int nsize = sizeof(SOCKADDR);
	SOCKET client = accept(_socket, &clientAddr, &nsize);
	if (client != INVALID_SOCKET)
	{
		addClient(client);
	}
}

void NetMoudle::addClient(SOCKET socket)
{
	auto user = new ClientUser(socket);
	m_ClientUsersVec.push_back(user);
	user->Init();
}



