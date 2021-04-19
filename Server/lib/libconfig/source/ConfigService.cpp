#include "ConfigService.h"
#include <io.h>
#include <singleton.h>
#include <iostream>


static ConfigService* g_ConfigModule = nullptr;
ConfigService& ConfigService::getInstance()
{
	// TODO: 在此处插入 return 语句
	if (!g_ConfigModule)
	{
		g_ConfigModule = new ConfigService();
	}
	return *g_ConfigModule;
}


bool ConfigService::Init()
{
	return LoadTableConfig();
}

bool ConfigService::Update()
{
	return true;
}

bool ConfigService::Shut()
{
	return true;
}

tbsChessTypeItem* ConfigService::cfgChessTypeTableItem(int idx)
{
	return Singleton<cfgChessTypeTable>::Instance()->GetTableItem(idx);
}

tbsGlobalCfgItem* ConfigService::tbsGlobalCfgItemItem()
{
	return Singleton<cfgGlobalCfgTable>::Instance()->GetTableItem(1);
}

tbsDatabaseCfgItem* ConfigService::tbsDatabaseCfgItem(int idx)
{
	return Singleton<cfgDatabaseCfgTable>::Instance()->GetTableItem(idx);
}
