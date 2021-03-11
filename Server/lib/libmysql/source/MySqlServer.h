#pragma once
#include <iostream>
#include "MySqlQueryResult.h"
#include <Moudle.h>
#include <memory>

struct MYSQL;
class MySqlServer:public Moudle
{
public:
	MySqlServer();
	~MySqlServer();

	static MySqlServer& getInstance();
	// 通过 IModule 继承
	virtual void Init()override;
	virtual void Update()override;
	virtual void Shut()override;

	void test();

public:
	bool Query(IQueryResult* result, char*);//查询

	std::shared_ptr<MySqlQueryResult> Query(std::string Expression);

	bool Execute(std::string expression);//执行

private:
	MYSQL* myCont{};
	char _temp[256]{};
};
