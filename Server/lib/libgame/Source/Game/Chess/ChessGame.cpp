#include "ChessGame.h"
#include <MsgMgr.h>

using namespace std;

void ChessGame::Init()
{
	//todo: Init Board
}

void ChessGame::Start()
{
	MsgPB::Msg_Chess_Start_S2C msg;
	msg.set_gameid(m_GameId);

	//todo: send startmsg
}

void ChessGame::Update()
{
}

void ChessGame::Shut()
{
}

void ChessGame::onMsg_Chess_Action_C2S(const Msg_Chess_Action_C2S& msg)
{
	//todo: 
}

bool ChessGame::ckeckGameOver(int x, int y)
{
	//todo:
	return false;
}
