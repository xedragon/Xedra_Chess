#include <Facade.h>
#include <thread>
#include <Moudle.h>
#include <libconfig/source/ConfigModule.h>
#include <Moudle/NetMoudle.h>
#include <libmysql/source/MySqlServer.h>
#include <libgame/Source/Game/Gobang/GobangManager.h>

using namespace std;

static Facade* g_Facade=nullptr;
Facade& Facade::getInstance()
{
	if (!g_Facade)
	{
		g_Facade = new Facade();
	}
	return *g_Facade;
}

bool Facade::Init()
{
	ConfigModule::getInstance().Init();
	MySqlServer::getInstance().Init();
	GobangManager::getInstance().Init();
	NetMoudle::getInstance().Init();

	RegisterMoudle(&ConfigModule::getInstance());
	RegisterMoudle(&MySqlServer::getInstance());
	RegisterMoudle(&GobangManager::getInstance());
	RegisterMoudle(&NetMoudle::getInstance());
	return true;
}

bool Facade::Update()
{
	for (auto&& moudle : m_MoudleVec)
	{
		moudle->Update();
	}
	return true;
}

void Facade::Start()
{
	Init();

	while (true)
	{
		if (!Update())
			break;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void Facade::RegisterMoudle(Moudle* moudle)
{
	m_MoudleVec.push_back(moudle);
}
