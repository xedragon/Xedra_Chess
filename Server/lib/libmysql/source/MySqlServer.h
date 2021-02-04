#pragma once
#include <iostream>


//数据库信息，仅连接时使用
struct sqlinfo
{
	const char* host;
	const char* user;
	const char* password;
	const char* database;
	unsigned int port;
	const char unix_socket;
	unsigned long clientflag;
	sqlinfo() :
		host("127.0.0.1"),
		port(3306),
		user("root"),
		password("456258"),
		database("class"),
		unix_socket(NULL),
		clientflag(0)
	{

	}
};

class IQueryResult;
struct MYSQL;

class MySqlServer
{
public:
	MySqlServer();
	~MySqlServer();

	static MySqlServer& getInstance();
	// 通过 IModule 继承
	virtual bool Init();
	virtual bool Update();
	virtual bool Shut();

private:
	bool Query(IQueryResult** result, char*);//查询
	bool Execute(char*);//执行

private:
	sqlinfo m_sqlinfo{};
	MYSQL* myCont{};
};
