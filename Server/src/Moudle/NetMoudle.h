#pragma once
#include <WinSock2.h>
#include <Moudle/Moudle.h>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class ClientUser;
class NetMoudle :public Moudle
{
public:
	NetMoudle();
	static NetMoudle& getInstance();
public:
	virtual void Init();
	virtual void Update() ;
	virtual void Shut() ;
	void Accept();
private:
	SOCKET _socket{};
	SOCKADDR clientAddr{};

	std::vector<ClientUser*> m_ClientUsersVec{};
};


