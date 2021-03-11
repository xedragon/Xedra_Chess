#include "ChessManager.h"

using namespace std;

static ChessManager* g_ChessManager{};
ChessManager& ChessManager::getInstance()
{
	// TODO: 在此处插入 return 语句
	if (!g_ChessManager)
	{
		g_ChessManager = new ChessManager();
	}
	return *g_ChessManager;
}

void ChessManager::Init()
{
}

void ChessManager::Update()
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

void ChessManager::Shut()
{
}

void ChessManager::addMatch(ClientUser* user)
{
	m_MatchQueue.push_back(user);
}

void ChessManager::AssignGame(ClientUser* user1, ClientUser* user2)
{
	auto&& game = new ChessGame(user1, user2, m_serial);
	m_GameVec.emplace(m_serial++,game);
}
