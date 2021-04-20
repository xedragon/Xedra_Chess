#include <ClientUser.h>
#include <iostream>
#include <MsgMgr.h>
#include <time.h>
#include <Game/Gobang/GobangGame.h>
#include <Game/Gobang/GobangManager.h>

#include <Game/Chess/ChessGame.h>
#include <Game/Chess/ChessManager.h>

#include "MySqlService.h"
using namespace std;

ClientUser::ClientUser(SOCKET socket)
{
	m_MsgMgr = std::make_shared<MsgMgr>(this, socket);
	_socket = socket;
	std::cout << fmt::format("用户{0}连接\n", socket);
}

bool ClientUser::Init()
{
	//注册消息
	m_MsgMgr->RegisterProMsg(this, &ClientUser::onLogin_C2S);

	//Gobang
	m_MsgMgr->RegisterProMsg(this, &ClientUser::onMsg_Gobang_Match_C2S);
	m_MsgMgr->RegisterProMsg(this, &ClientUser::onMsg_Gobang_Action_C2S);
	m_MsgMgr->RegisterProMsg(this, &ClientUser::onMsg_Gobang_Giveup_C2S);
	m_MsgMgr->RegisterProMsg(this, &ClientUser::onMsg_Gobang_Regret_C2S);
	m_MsgMgr->RegisterProMsg(this, &ClientUser::onMsg_Gobang_Pause_C2S);

	//Chess
	m_MsgMgr->RegisterProMsg(this, &ClientUser::onMsg_Chess_Match_C2S);
	m_MsgMgr->RegisterProMsg(this, &ClientUser::onMsg_Chess_Action_C2S);
	m_MsgMgr->RegisterProMsg(this, &ClientUser::onMsg_Chess_Giveup_C2S);
	m_MsgMgr->RegisterProMsg(this, &ClientUser::onMsg_Chess_Regret_C2S);
	m_MsgMgr->RegisterProMsg(this, &ClientUser::onMsg_Chess_Pause_C2S);

	Msg_Connect_S2C msg;
	m_MsgMgr->SendMsg(msg);
	return true;
}

bool ClientUser::Update()
{
	return m_MsgMgr->Update();
}

bool ClientUser::Shut()
{
	std::cout << fmt::format("用户{0}退出\n", _socket);
	if (m_pChessGame)
		ChessManager::getInstance().ShutGame(m_pChessGame->getGameID());
	if (m_pGobangGame)
		GobangManager::getInstance().ShutGame(m_pGobangGame->getGameID());
	return false;
}


MsgMgr* ClientUser::getMsgMgr()
{
	return m_MsgMgr.get();
}

void ClientUser::joinGobang(GobangGame* game)
{
	m_pGobangGame = game;
}

void ClientUser::joinChess(ChessGame* game)
{
	m_pChessGame = game;
}

void ClientUser::exitGobang()
{
	m_pGobangGame = nullptr;
}

void ClientUser::exitChess()
{
	m_pChessGame = nullptr;
}

GobangGame* ClientUser::getGobangGame()
{
	return m_pGobangGame;
}

void ClientUser::onLogin_C2S(const Msg_Login_C2S& msg)
{
	Msg_Login_S2C reply;

	cout << "User Loginin: " << msg.szname() << endl;
	if (msg.conmethod() == Msg_Login_C2S::CONMETHOD::Msg_Login_C2S_CONMETHOD_Login)
	{
		//登录
		auto expreesion = fmt::format("Select id,name,password from user where name = '{0}';", msg.szname());
		auto result = MySqlService::getInstance().Query(expreesion);
		if (result)
		{
			result->Read();
			if (result->get_string(2) == msg.szpassword())
			{
				ConenctToAccount(msg.szname());
				cout << "验证成功" << endl;
				reply.set__errorcode(Msg_Login_S2C::ERRORCODE::Msg_Login_S2C_ERRORCODE_LoginSuccess);
			}
			else
			{
				cout << "密码错误" << endl;
				reply.set__errorcode(Msg_Login_S2C::ERRORCODE::Msg_Login_S2C_ERRORCODE_ErrorPassword);
			}
		}
		else
		{
			cout << "不存在该用户" << endl;
			reply.set__errorcode(Msg_Login_S2C::ERRORCODE::Msg_Login_S2C_ERRORCODE_EmptyAccount);
		}
	}
	else if (msg.conmethod() == Msg_Login_C2S::CONMETHOD::Msg_Login_C2S_CONMETHOD_Regist)
	{
		//注册
		auto expreesion = fmt::format("insert into user(name, password) values('{0}', '{1}');", msg.szname(), msg.szpassword());
		if (MySqlService::getInstance().Execute(expreesion))
		{
			cout << "注册成功" << endl;
			ConenctToAccount(msg.szname());
			reply.set__errorcode(Msg_Login_S2C::ERRORCODE::Msg_Login_S2C_ERRORCODE_LoginSuccess);
		}
		else
		{
			cout << "注册失败" << endl;
			reply.set__errorcode(Msg_Login_S2C::ERRORCODE::Msg_Login_S2C_ERRORCODE_ExistedName);
		}
	}

	reply.set_logintimestamp(time(nullptr));
	reply.set_id(_id);
	m_MsgMgr->SendMsg(reply);
}

void ClientUser::onMsg_Gobang_Match_C2S(const Msg_Gobang_Match_C2S& msg)
{
	//Todo: begin matching
	GobangManager::getInstance().addMatch(this);
}

void ClientUser::onMsg_Gobang_Action_C2S(const Msg_Gobang_Action_C2S& msg)
{
	if (m_pGobangGame)
		m_pGobangGame->onMsg_Gobang_Action_C2S(msg);
}

void ClientUser::onMsg_Gobang_Giveup_C2S(const Msg_Gobang_Giveup_C2S& msg)
{
	if (m_pGobangGame)
		m_pGobangGame->onMsg_Gobang_Giveup_C2S(msg);
}

void ClientUser::onMsg_Gobang_Regret_C2S(const Msg_Gobang_Regret_C2S& msg)
{
	if (m_pGobangGame)
		m_pGobangGame->onMsg_Gobang_Regret_C2S(msg);
}

void ClientUser::onMsg_Gobang_Pause_C2S(const Msg_Gobang_Pause_C2S& msg)
{
	if (m_pGobangGame)
		m_pGobangGame->onMsg_Gobang_Pause_C2S(msg);
}

void ClientUser::onMsg_Chess_Match_C2S(const Msg_Chess_Match_C2S& msg)
{
	//Todo: begin matching
	ChessManager::getInstance().addMatch(this);
}

void ClientUser::onMsg_Chess_Action_C2S(const Msg_Chess_Action_C2S& msg)
{
	if (m_pChessGame)
		m_pChessGame->onMsg_Chess_Action_C2S(msg);
}

void ClientUser::onMsg_Chess_Giveup_C2S(const Msg_Chess_Giveup_C2S& msg)
{
	if (m_pChessGame)
		m_pChessGame->onMsg_Chess_Giveup_C2S(msg);
}

void ClientUser::onMsg_Chess_Regret_C2S(const Msg_Chess_Regret_C2S& msg)
{
	if (m_pChessGame)
		m_pChessGame->onMsg_Chess_Regret_C2S(msg);
}

void ClientUser::onMsg_Chess_Pause_C2S(const Msg_Chess_Pause_C2S& msg)
{
	if (m_pChessGame)
		m_pChessGame->onMsg_Chess_Pause_C2S(msg);
}

void ClientUser::ConenctToAccount(std::string name)
{
	auto expreesion = fmt::format("Select id,name from user where name = '{0}';", name);
	auto result = MySqlService::getInstance().Query(expreesion);
	if (result && result->Read())
	{
		_id = result->get_int(0);
		_name = result->get_string(1);
	}
}
