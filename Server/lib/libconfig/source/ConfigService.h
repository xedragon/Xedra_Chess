#pragma once
#include "automake\tableconfig.h"
#include <Moudle.h>

class ConfigService:public Moudle
{
public:
	static ConfigService& getInstance();
public:
	bool Init()override;
	bool Update()override;
	bool Shut()override;
public:
	tbsChessTypeItem* cfgChessTypeTableItem(int idx);
	tbsGlobalCfgItem* tbsGlobalCfgItemItem();
	tbsDatabaseCfgItem* tbsDatabaseCfgItem(int idx);
};

