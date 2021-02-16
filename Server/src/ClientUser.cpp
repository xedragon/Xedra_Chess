#include <ClientUser.h>
#include <MsgMgr.h>
using namespace std;

ClientUser::ClientUser(SOCKET socket)
{
	m_MsgMgr = std::make_shared<MsgMgr>(socket);
}

bool ClientUser::Init()
{
	//注册消息
	m_MsgMgr->RegisterProMsg(this,&ClientUser::onLogin);

	//
	Msg_Connect_S2C msg;
	m_MsgMgr->SendMsg(msg);
	return true;
}

void ClientUser::test()
{
	cout << "测试新用户" << endl;

	Msg_Login_C2S msg;
	msg.set_szname("wocao");
	msg.set_szpassword("wocao");
	msg.set_conmethod(1);
	msg.set_msgid(MsgType::LOGIN_C2S);

	m_MsgMgr->NotifyMsg(msg);
	m_MsgMgr->SendMsg(msg);
}

bool ClientUser::Update()
{
	m_MsgMgr->Update();
	return false;
}

bool ClientUser::Shut()
{
	return false;
}


MsgMgr* ClientUser::getMsgMgr()
{
	return m_MsgMgr.get();
}

void ClientUser::onLogin(const Msg_Login_C2S& msg)
{
	cout << "Name:" << msg.szname() << "	Password:" << msg.szpassword() << endl;

	Msg_Login_S2C back;
	back.set_logintimestamp(2254);
	m_MsgMgr->SendMsg(back);
	m_MsgMgr->SendMsg(back);
}
