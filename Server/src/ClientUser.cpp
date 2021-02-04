#include <ClientUser.h>

ClientUser::ClientUser(SOCKET socket)
{
	_socket = socket;
}

bool ClientUser::Update()
{
	//Receive
	{
		char szBuf[255];
		int nLen = recv(_socket, szBuf, 255, 0);
		if (nLen > 0)
		{
			PushMsg(szBuf, nLen);
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
				LogError(error);
			}
		}
	}
	//Send
	{
		int nLen = send(_socket, m_SendBuf, m_SendBufLen, 0);
		if (nLen > 0)
		{
			memmove(m_SendBuf, m_SendBuf + nLen, m_SendBufLen - nLen);
			m_SendBufLen -= nLen;
		}
	}
	return false;
}

bool ClientUser::Shut()
{
	return false;
}

void ClientUser::PushMsg(char* szMsg, int nLen)
{
	memcpy(m_RecvBuf + m_RecvBufLen, szMsg, nLen);
	m_RecvBufLen += nLen;

	while (m_RecvBufLen >= MSGHEADLEN)
	{
		int msgType = (INT16)(m_RecvBufLen);
		int msgSize = (INT16)(m_RecvBufLen + 2);

		if (m_RecvBufLen >= msgSize + 4)
		{
			//contain a whole protomsg
			
		}
		else
		{
			//don't contain a whole protomsg
			break;
		}

		m_RecvBufLen -= msgSize;
		memmove(m_RecvBuf, m_RecvBuf + msgSize, m_RecvBufLen);
	}
}

void ClientUser::LogError(DWORD error)
{
}

void ClientUser::SendMsg(char* pMsg, int len)
{
	memcpy(m_SendBuf + m_SendBufLen, pMsg, len);
	m_SendBufLen += len;
}
