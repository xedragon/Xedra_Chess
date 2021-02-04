#include "NetMoudle.h"
#include <iostream>
#include <Facade.h>
#include <ClientUser.h>
#include <libconfig/source/DataService.h>
#include <libconfig/source/automake/tableconfig.h>
using namespace std;
#pragma comment(lib,"ws2_32")

NetMoudle::NetMoudle()
{
	Facade::getInstance().RegisterMoudle(this);
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

void NetMoudle::Init()
{
	auto&& GloabalCfg = DataService::getInstance().tbsGlobalCfgItemItem();
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
	listen(_socket, 1);//开始监听

	return;
}

void NetMoudle::Update()
{
	Accept();

	for (auto&& user : m_ClientUsersVec)
	{
		user->Update();
	}
}

void NetMoudle::Shut()
{
}

void NetMoudle::Accept()
{
	int nsize = sizeof(SOCKADDR);
	SOCKET client = accept(_socket, &clientAddr, &nsize);//连接阶段
	if (client != INVALID_SOCKET)
	{
		ClientUser* user = new ClientUser(client);
	}
}

