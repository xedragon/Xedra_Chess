#pragma once
#include <vector>

#include "CardConfig.h"
class CardTable : public BaseTable
{
public:
	CardTable() :BaseTable("Card.bin") {}
	virtual IData* ReadRow(int &id) override
	{
		auto config = new CardDefine(); 
		int enumTmp;

		const char* data;

		ReadValue(config->id);
		ReadValue(config->card_id);
		ReadValue(config->desc);
		ReadValue(config->image);
		ReadValue(config->card_type);
		ReadValue(config->card_attribute);
		ReadValue(config->card_point);
		ReadValue(config->card_name);
		ReadValue(config->card_num);
		id=config->id;
		return (IData*)config;
	}
};
ITable* DataService::LoadTable(const char* name)
{
	BaseTable *pTable = nullptr;

	if(strcmp("class CardDefine", name)==0)
	{
		pTable = new CardTable();
	}
	pTable->Load();
	return pTable;
}