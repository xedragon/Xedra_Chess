#include <MySqlServer.h>
#include <include/mysql.h>
#include "../../libconfig/source/ConfigModule.h"
#include "../../libbaseutil/source/format.h"

using namespace std;

static MySqlServer* g_MySqlServer=nullptr;
MySqlServer::MySqlServer()
{
	
}
MySqlServer::~MySqlServer()
{
	g_MySqlServer = nullptr;
}

MySqlServer& MySqlServer::getInstance()
{
	// TODO: 在此处插入 return 语句
	if (!g_MySqlServer)
	{
		g_MySqlServer = new MySqlServer();
	}
	return *g_MySqlServer;
}

void MySqlServer::Init()
{
	auto cfgItem = ConfigModule::getInstance().tbsDatabaseCfgItem(1);
	if (!cfgItem)
	{
		printf("Load DatabaseCfg Error\n");
		return;
	}

	myCont = mysql_init(myCont);
	if (mysql_real_connect(myCont, cfgItem->host.c_str(), cfgItem->user.c_str(), cfgItem->password.c_str(), cfgItem->database.c_str(), cfgItem->port, (char *)cfgItem->unix_socket, cfgItem->clientflag))
	{
		printf("connect success!\n");
	}
	else
	{
		printf("connect failed!\n");
	}
	mysql_query(myCont, "SET NAMES GBK"); //设置编码格式
}

void MySqlServer::Update()
{
	
}

void MySqlServer::Shut()
{
	mysql_close(myCont);//断开连接
}

void MySqlServer::test()
{
	auto tester = Query("select * from user");
	if (tester)
	{
		while (tester->Read())
		{
			auto name = tester->get_string(1);
			auto password = tester->get_string(2);
			cout << __FILE__ << __LINE__ << __FUNCTION__;
			cout<<"name:"<<name<<" passworld:"<<password<<endl;
		}
	}
	else
	{
		cout << "test failed" << endl;
	}
}

bool MySqlServer::Execute(std::string QueryCode)
{
	if (mysql_query(myCont, QueryCode.c_str()))
	{
		printf("执行sql语句失败，错误信息为:%s\n", mysql_error(myCont));
		return false;
	}
	return true;
}

bool MySqlServer::Query(IQueryResult *result,char *QueryCode)
{
	if (mysql_query(myCont, QueryCode))
	{
		printf("执行sql查询语句失败，错误信息为:%s\n", mysql_error(myCont));
		return false;
	}

	MYSQL_RES *res = mysql_store_result(myCont);
	if (res)
		result=new MySqlQueryResult(res, res->row_count, res->field_count);
	return true;
}

//std::shared_ptr<MySqlQueryResult> MySqlServer::Query(char* Expression, ...)
//{
//	va_list ArgList;
//	va_start(ArgList,Expression);
//	vsprintf_s(_temp,Expression, ArgList);
//	va_end(ArgList);
//
//	return Query(_temp);
//}

std::shared_ptr<MySqlQueryResult> MySqlServer::Query(std::string Expression)
{
	if (mysql_query(myCont, Expression.c_str()))
	{
		printf("执行sql查询语句失败，错误信息为:%s\n", mysql_error(myCont));
		return nullptr;
	}
	MYSQL_RES* res = mysql_store_result(myCont);

	return std::make_shared<MySqlQueryResult>(res, res->row_count, res->field_count);
}
