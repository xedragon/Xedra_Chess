#pragma once
#include <iostream>
#include <BaseUtil.h>
#include <deque>
#include <mutex>

#include <ClientUser.h>
#include <Game/GameManager.h>
#include <Game/Gobang/GobangGame.h>

class GobangManager :public GameManager
{
public:
	static GobangManager& getInstance();
public:
	bool Init()override;
	bool Update()override;
	bool Shut()override;
public:
	void addMatch(ClientUser* user);
	bool AssignGame(ClientUser* user1, ClientUser* user2);
	bool ShutGame(int gameID);
private:
	std::deque<ClientUser*> m_MatchQueue{ };	//匹配队列
	std::map<int, GobangGame*> m_GameVec{};		//进行中的游戏
	std::mutex m_mutex{};

	int m_serial{};
};