#pragma once
#include <WinSock2.h>
#include <Moudle/Moudle.h>
#include <vector>

class ClientUser;
class NetMoudle :Moudle
{
public:
	NetMoudle();
	static NetMoudle& getInstance();
public:
	virtual void Init()override;
	virtual void Update() override;
	virtual void Shut() override;
	void Accept();
private:
	SOCKET _socket;
	SOCKADDR clientAddr;

	std::vector<ClientUser*> m_ClientUsersVec{};
};