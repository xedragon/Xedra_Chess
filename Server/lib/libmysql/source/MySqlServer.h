#pragma once
#include <iostream>


//���ݿ���Ϣ��������ʱʹ��
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
	// ͨ�� IModule �̳�
	virtual bool Init();
	virtual bool Update();
	virtual bool Shut();

private:
	bool Query(IQueryResult** result, char*);//��ѯ
	bool Execute(char*);//ִ��

private:
	sqlinfo m_sqlinfo{};
	MYSQL* myCont{};
};
