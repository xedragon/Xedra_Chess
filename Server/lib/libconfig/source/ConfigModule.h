#pragma once
#include "automake\tableconfig.h"
#include <Moudle.h>

class ConfigModule:public Moudle
{
public:
	static ConfigModule& getInstance();
public:
	void Init()override;
	void Update()override;
	void Shut()override;
	bool Test();
public:
	tbsChessTypeItem* cfgChessTypeTableItem(int idx);
	tbsGlobalCfgItem* tbsGlobalCfgItemItem();
	tbsDatabaseCfgItem* tbsDatabaseCfgItem(int idx);
};

