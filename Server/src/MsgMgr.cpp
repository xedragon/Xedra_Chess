#include <MsgMgr.h>

using namespace std;

void MsgMgr::RegisterProMsg(UINT16 msgid, CallBack* callback)
{
	m_CallBackMap.emplace(msgid, callback);
}

bool MsgMgr::Init()
{
	return false;
}

bool MsgMgr::Update()
{
	//Receive
	{
		char szBuf[2];
		int nLen = recv(_socket, szBuf, 2, 0);
		if (nLen > 0)
		{
			Decode(szBuf, nLen);
		}
		else
		{
			auto error = GetLastError();
			if (error != WSAEWOULDBLOCK)
			{
				return false;
			}
			else
			{
				//cout << "Socket Recv Errored:"<<error;
			}
		}
	}
	//Send
	{
		int nLen = send(_socket, m_SendBuf.c_str(), m_SendBuf.length(), 0);
		if (nLen > 0)
		{
			m_SendBuf.erase(0, nLen);
		}
	}
	return true;
}

bool MsgMgr::Shut()
{
	return false;
}

void MsgMgr::setSocket(SOCKET socket)
{
	_socket = socket;
}

void MsgMgr::Decode(char* szMsg, int nLen)
{
	m_RecvBuf.append(szMsg, nLen);

	while (m_RecvBuf.length() >= MSGHEADLEN)
	{
		auto msgSize = *(UINT16*)(m_RecvBuf.c_str());
		auto msgType = *(UINT16*)(m_RecvBuf.c_str() + 2);

		if (m_RecvBuf.length() >= msgSize + 4)
		{
			//contain a whole protomsg
			NotifyMsg(msgType, m_RecvBuf.c_str() + 4, msgSize);
		}
		else
		{
			//don't contain a whole protomsg
			break;
		}

		m_RecvBuf.erase(0, msgSize + 4);
	}
}

void MsgMgr::SendMsg(char* pMsg, UINT16 size, UINT16 type)
{
	m_SendBuf.append((char*)&size, 2);
	m_SendBuf.append((char*)&type, 2);
	m_SendBuf.append(pMsg, size);
}

void MsgMgr::NotifyMsg(UINT16 msgid, const::google::protobuf::Message& msg)
{
	auto&& range = m_CallBackMap.equal_range(msgid);

	for (auto&& itr = range.first; itr != range.second; itr++)
	{
		itr->second->invoke(msg);
	}
}

void MsgMgr::NotifyMsg(UINT16 msgid, const char* buff, UINT16 len)
{
	auto&& range = m_CallBackMap.equal_range(msgid);

	for (auto&& itr = range.first; itr != range.second; itr++)
	{
		itr->second->invoke(buff,len);
	}
}


