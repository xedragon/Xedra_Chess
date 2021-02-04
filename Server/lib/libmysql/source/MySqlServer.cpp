#include <MySqlServer.h>
#include <include\mysql.h>
#include <MySqlQueryResult.h>

using namespace std;

//void main()
//{
//	std::cout << "..";
//}

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

bool MySqlServer::Init()
{
	myCont = mysql_init(myCont);
	if (mysql_real_connect(myCont, m_sqlinfo.host, m_sqlinfo.user, m_sqlinfo.password, m_sqlinfo.database, m_sqlinfo.port, (char *)m_sqlinfo.unix_socket, m_sqlinfo.clientflag))
	{
		printf("connect success!\n");
	}
	else
	{
		printf("connect failed!\n");
	}
	mysql_query(myCont, "SET NAMES GBK"); //设置编码格式

	return true;
}

bool MySqlServer::Update()
{
	return true;
}

bool MySqlServer::Shut()
{
	mysql_close(myCont);//断开连接
	return true;
}

bool MySqlServer::Execute(char *QueryCode)
{
	if (mysql_query(myCont, QueryCode))
	{
		printf("执行sql语句失败，错误信息为:%s\n", mysql_error(myCont));
		return false;
	}
	return true;
}

bool MySqlServer::Query(IQueryResult **result,char *QueryCode)
{
	*result = 0;
	if (mysql_query(myCont, QueryCode))
	{
		printf("执行sql查询语句失败，错误信息为:%s\n", mysql_error(myCont));
		return false;
	}
	MYSQL_RES *res = mysql_store_result(myCont);
	if (res)
		*result=new MySqlQueryResult(res, res->row_count, res->field_count);
	return true;
}