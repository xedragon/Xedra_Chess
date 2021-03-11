#pragma once
#include <iostream>
#include <WinSock2.h>
#include <map>
#include <functional>

#include <msg/Msg.pb.h>
using namespace std;
using namespace MsgPB;

#define MSGHEADLEN 4

class CallBack
{
public:
	virtual void invoke(const ::google::protobuf::Message& msg) = 0;
	virtual void invoke(const char* buff, UINT16 len) = 0;
};

template<typename T>
class MsgCallBack :public CallBack
{
	using callback = void(*)(const T& msg);
public:
	MsgCallBack(const std::function<void(const T& evt)>& callback)
	{
		m_callback = callback;
	}

	virtual void invoke(const ::google::protobuf::Message& msg)override
	{
		m_callback(static_cast<const T&>(msg));
	}
	virtual void invoke(const char* buff, UINT16 len)override
	{
		T msg;
		msg.ParseFromArray(buff, len);

		invoke(msg);
	}
private:
	std::function<void(const T& evt)> m_callback;
};

class MsgHandler
{
public:
};


class ClientUser;

class MsgMgr
{
public:
	MsgMgr(ClientUser* user,SOCKET socket) :_socket(socket),_User(user) {}
public:
	bool Init();
	bool Update();
	bool Shut();
public:
	void setSocket(SOCKET socket);
	void Decode(char* szMsg, int nLen);

	template<typename ClassT, typename ParamT>
	bool RegisterProMsg(ClassT* pHandler, void(ClassT::* method)(ParamT));
	void RegisterProMsg(UINT16 msgid, CallBack* callback);

	template<typename MsgT>
	void SendMsg(const MsgT& msg);
	void SendMsg(char* pMsg, UINT16 size, UINT16 type);

	template<typename MsgT>
	void NotifyMsg(const MsgT& msg);
	void NotifyMsg(UINT16 msgid, const ::google::protobuf::Message& msg);
	void NotifyMsg(UINT16 msgid, const char* buff, UINT16 len);
private:
	ClientUser* GetClientUser()
	{
		return _User;
	}
private:
	SOCKET _socket{};
	ClientUser* _User{};

	string m_RecvBuf{};
	string m_SendBuf{};

	std::multimap<int, CallBack*> m_CallBackMap{};
};

template<typename ClassT, typename ParamT>
bool MsgMgr::RegisterProMsg(ClassT* pHandler, void(ClassT::* method)(ParamT))
{
	std::function<void(const ParamT&)> func = std::bind(method, pHandler, std::placeholders::_1);
	CallBack* callback = new MsgCallBack<std::remove_cv_t<std::remove_reference_t<ParamT>>>(func);

	RegisterProMsg(std::remove_cv_t<std::remove_reference_t<ParamT>>::default_instance().msgid(), callback);
	return true;
}

template<typename MsgT>
inline void MsgMgr::SendMsg(const MsgT& msg)
{
	std::string strData;
	msg.SerializeToString(&strData);

	SendMsg((char*)strData.c_str(), strData.size(), MsgT::default_instance().msgid());
}

template<typename MsgT>
inline void MsgMgr::NotifyMsg(const MsgT& msg)
{
	NotifyMsg(MsgT::default_instance().msgid(), msg);
}