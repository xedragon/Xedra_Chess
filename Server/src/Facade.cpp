#include <Facade.h>
#include <thread>
#include <Moudle/NetMoudle.h>
#include <libmysql/source/MySqlService.h>
#include <libconfig/source/ConfigService.h>
#include <libgame/Source/Game/Gobang/GobangManager.h>
#include <libgame/Source/Game/Chess/ChessManager.h>

using namespace std;

static Facade* g_Facade = nullptr;
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
	RegisterMoudle<ConfigService>();
	RegisterMoudle<MySqlService>();

	RegisterMoudle<GobangManager>();
	RegisterMoudle<ChessManager>();

	RegisterMoudle<NetMoudle>();
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

bool Facade::Shut()
{
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
	moudle->Init();
	m_MoudleVec.push_back(moudle);
	std::cout <<"Load Module: "<< typeid(*moudle).name() << endl;
}

void Facade::UnRegisterMoudle(Moudle* moudle)
{
	moudle->Shut();
	auto itr = std::find(m_MoudleVec.begin(), m_MoudleVec.end(), moudle);
	if (itr != m_MoudleVec.end())
	{
		m_MoudleVec.erase(itr);
	}
	std::cout << "Unload Module: " << typeid(*moudle).name() << endl;
}
