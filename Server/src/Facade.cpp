#include <Facade.h>
#include <thread>
#include <Moudle/Moudle.h>
#include <Moudle/NetMoudle.h>
#include <libconfig/source/DataService.h>
#include <msg/source/msg/Msg.pb.h>

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
	DataService::getInstance().Init();
	NetMoudle::getInstance().Init();
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
	/*Init();

	while (true)
	{
		if (!Update())
			break;
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}*/
}

void Facade::RegisterMoudle(Moudle* moudle)
{
	m_MoudleVec.push_back(moudle);
}
