#include "NetMoudle.h"
#include <iostream>
#include <Facade.h>
#include <ClientUser.h>
#include <libconfig/source/DataService.h>
#include <libconfig/source/automake/tableconfig.h>
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

void NetMoudle::Init()
{
	//初始化
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in sockaddr;
	sockaddr.sin_family = PF_INET;
	sockaddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	sockaddr.sin_port = htons(235);
	//sockaddr.sin_port = htons(GloabalCfg->ServerPort);

	//非阻塞模式
	int mode = 1;
	ioctlsocket(_socket, FIONBIO, (u_long*)&mode);

	//绑定端口
	bind(_socket, (const struct sockaddr*)&sockaddr, sizeof(sockaddr));
	listen(_socket, 1);//开始监听

	Facade::getInstance().RegisterMoudle(this);
}

void NetMoudle::Update()
{
	Accept();
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
		cout << "新用户连接" << endl;
	}
}



