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

void GobangManager::Init()
{
}

void GobangManager::Update()
{
	m_mutex.lock();
	while (m_MatchQueue.size() >= 1)
	{
		AssignGame(m_MatchQueue[0], m_MatchQueue[0]);
		m_MatchQueue.pop_front();
		//m_MatchQueue.pop_front();
	}
	m_mutex.unlock();
}

void GobangManager::Shut()
{
}

void GobangManager::addMatch(ClientUser* user)
{
	m_MatchQueue.push_back(user);
}

void GobangManager::AssignGame(ClientUser* user1, ClientUser* user2)
{
	auto&& game = new GobangGame(user1, user2, m_serial);
	m_GameVec.emplace(m_serial++,game);
}
