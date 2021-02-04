#include "DataService.h"
#include <io.h>
#include <singleton.h>
#include <iostream>


static DataService* g_DataService = nullptr;
DataService& DataService::getInstance()
{
	// TODO: �ڴ˴����� return ���
	if (!g_DataService)
	{
		g_DataService = new DataService();
	}
	return *g_DataService;
}


bool DataService::Init()
{
	return LoadTableConfig();
}

bool DataService::Test()
{
	auto item = Singleton<cfgChessTypeTable>::Instance()->GetTableItem(1);
	if (item != nullptr)
	{
		std::cout << item->type;
	}

	return true;
}

tbsChessTypeItem* DataService::cfgChessTypeTableItem(int idx)
{
	return Singleton<cfgChessTypeTable>::Instance()->GetTableItem(idx);
}

tbsGlobalCfgItem* DataService::tbsGlobalCfgItemItem()
{
	return Singleton<cfgGlobalCfgTable>::Instance()->GetTableItem(1);
}
