#include <MsgMgr.h>
#include <functional>
using namespace std;

template<typename ClassT, typename ParamT>
void MsgMgr::_reg(ClassT* pThis, void(ClassT::* func)(ParamT))
{
	RegisterProMsg(pThis, ParamT::default_instance().MsgId(), std::bind(func, pThis, std::placeholders::_1));
}

template<typename ClassT, typename ParamT>
inline bool MsgMgr::RegisterProMsg(ClassT* pHandler, void(ClassT::* method)(ParamT))
{
	std::function<void(ParamT)> func = std::bind(method, pHandler, std::placeholders::_1);
	Msg_Login_C2S msg;
	func(msg);
	return false;
}

