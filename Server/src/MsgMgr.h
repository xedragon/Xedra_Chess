#pragma once
#include <iostream>
using namespace std;


class MsgHandler
{
public:
};


class MsgMgr
{
public:
	template<typename ClassT, typename ParamT>
	void _reg(ClassT* pThis, void(ClassT::* func)(ParamT));

	template<typename ClassT,typename ParamT>
	bool RegisterProMsg(ClassT* pHandler, void(ClassT::* method)(ParamT));
private:
};

//template<typename MsgT, typename CallbackT>
//void reg(EventHandler* pHandler, const CallbackT& callback)
//{
//	reg(pHandler, MsgT::default_instance().msgtype(), new MsgCallback<MsgT>(callback));
//}
//void reg(EventHandler* pHandler, uint16 msgId, BaseMsgCallback* pCallback);
//void reg(EventHandler* pHandler, const tstring& msgName, BaseMsgCallback* pCallback);

//template<typename ThisT, typename ArgT> void __register_s2c(ThisT* pThis, void(ThisT::* method)(ArgT)) { NS::MsgMgr::getInstance().reg<std::remove_cv_t<std::remove_reference_t<ArgT>>>(pThis, std::bind(method, pThis, std::placeholders::_1)); }
//#define REGISTER_S2C(callback) __register_s2c(this, &std::remove_pointer<decltype(this)>::type::callback)

