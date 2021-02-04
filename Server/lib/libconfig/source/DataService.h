#pragma once
#include "automake\tableconfig.h"

class DataService
{
public:
	static DataService& getInstance();
public:
	bool Init();
	bool Test();
public:
	tbsChessTypeItem* cfgChessTypeTableItem(int idx);
	tbsGlobalCfgItem* tbsGlobalCfgItemItem();
};

