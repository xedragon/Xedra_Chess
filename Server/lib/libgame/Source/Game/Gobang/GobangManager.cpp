#include "GobangManager.h"

using namespace std;

static GobangManager* g_GobangManager{};
GobangManager& GobangManager::getInstance()
{
	// TODO: 在此处插入 return 语句
	if (!g_GobangManager)
	{
		g_GobangManager = new GobangManager();
	}
	return *g_GobangManager;
}

bool GobangManager::Init()
{
	return true;
}

bool GobangManager::Update()
{
	std::lock_guard<mutex> guard(m_mutex);

	while (m_MatchQueue.size() >= 2)
	{
		AssignGame(m_MatchQueue[0], m_MatchQueue[1]);
		m_MatchQueue.pop_front();
		m_MatchQueue.pop_front();
	}
	return true;
}

bool GobangManager::Shut()
{
	return true;
}

void GobangManager::addMatch(ClientUser* user)
{
	m_MatchQueue.push_back(user);
}

bool GobangManager::AssignGame(ClientUser* user1, ClientUser* user2)
{
	auto&& game = new GobangGame(user1, user2, m_serial);
	m_GameVec.emplace(m_serial++,game);

	return true;
}

bool GobangManager::ShutGame(int gameID)
{
	auto&& pGame = m_GameVec[gameID];
	if (!pGame)return false;

	bool bSucShut = pGame->Shut();
	delete pGame;
	pGame = nullptr;
	m_GameVec.erase(gameID);
	return true;
}
