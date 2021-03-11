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
	// ͨ�� IModule �̳�
	virtual void Init()override;
	virtual void Update()override;
	virtual void Shut()override;

	void test();

public:
	bool Query(IQueryResult* result, char*);//��ѯ

	std::shared_ptr<MySqlQueryResult> Query(std::string Expression);

	bool Execute(std::string expression);//ִ��

private:
	MYSQL* myCont{};
	char _temp[256]{};
};
