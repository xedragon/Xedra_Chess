#include "ConfigModule.h"
#include <io.h>
#include <singleton.h>
#include <iostream>


static ConfigModule* g_ConfigModule = nullptr;
ConfigModule& ConfigModule::getInstance()
{
	// TODO: 在此处插入 return 语句
	if (!g_ConfigModule)
	{
		g_ConfigModule = new ConfigModule();
	}
	return *g_ConfigModule;
}


void ConfigModule::Init()
{
	LoadTableConfig();
}

void ConfigModule::Update()
{

}

void ConfigModule::Shut()
{

}

bool ConfigModule::Test()
{
	auto item = Singleton<cfgChessTypeTable>::Instance()->GetTableItem(1);
	if (item != nullptr)
	{
		std::cout << item->type;
	}

	return true;
}

tbsChessTypeItem* ConfigModule::cfgChessTypeTableItem(int idx)
{
	return Singleton<cfgChessTypeTable>::Instance()->GetTableItem(idx);
}

tbsGlobalCfgItem* ConfigModule::tbsGlobalCfgItemItem()
{
	return Singleton<cfgGlobalCfgTable>::Instance()->GetTableItem(1);
}

tbsDatabaseCfgItem* ConfigModule::tbsDatabaseCfgItem(int idx)
{
	return Singleton<cfgDatabaseCfgTable>::Instance()->GetTableItem(idx);
}
