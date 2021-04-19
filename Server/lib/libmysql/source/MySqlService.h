#pragma once
#include <iostream>
#include "MySqlQueryResult.h"
#include <Moudle.h>
#include <memory>

struct MYSQL;
class MySqlService:public Moudle
{
public:
	MySqlService();
	~MySqlService();

	static MySqlService& getInstance();
	// ͨ�� IModule �̳�
	virtual bool Init()override;
	virtual bool Update()override;
	virtual bool Shut()override;

	void test();

public:
	std::shared_ptr<MySqlQueryResult> Query(std::string Expression);
	bool Execute(std::string expression);

private:
	MYSQL* myCont{};
	char _temp[256]{};
};
