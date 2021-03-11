#pragma once
#include <iostream>
#include <BaseUtil.h>
#include <mutex>
#include <ClientUser.h>
#include <Game/GameManager.h>
#include <Game/Chess/ChessGame.h>

class ChessManager :public GameManager
{
public:
	static ChessManager& getInstance();
public:
	void Init()override;
	void Update()override;
	void Shut()override;
public:
	void addMatch(ClientUser* user);
private:
	void AssignGame(ClientUser* user1, ClientUser* user2);
private:
	std::deque<ClientUser*> m_MatchQueue{ };	//匹配队列
	std::map<int, ChessGame*> m_GameVec{};		//进行中的游戏
	std::mutex m_mutex{};

	int m_serial{};
};