#pragma once
#include <BaseUtil.h>
#include <WinSock2.h>
#include <Moudle.h>

using namespace std;

class ClientUser;
class NetMoudle :public Moudle
{
public:
	NetMoudle();
	static NetMoudle& getInstance();
public:
	virtual bool Init();
	virtual bool Update() ;
	virtual bool Shut() ;
	void Accept();
private:
	void addClient(SOCKET socket);
private:
	SOCKET _socket{};
	SOCKADDR clientAddr{};

	std::vector<ClientUser*> m_ClientUsersVec{};
};


