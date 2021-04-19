#pragma once
#include <BaseUtil.h>
#include <Moudle.h>

class Facade
{
public:
	static Facade& getInstance();
public:
	bool Init();
	bool Update();
	bool Shut();

	void Start();
public:
	//查找模块
	template<class T>
	T* FindModule()
	{
		for (auto& mod : m_MoudleVec)
		{
			auto pResult = std::dynamic_cast<T*>(mod);
			if (pResult)return pResult;
		}
		return nullptr;
	}

	//加载模块
	void RegisterMoudle(Moudle* moudle);
	template<class T>
	inline void RegisterMoudle()
	{
		RegisterMoudle(&T::getInstance());
	}

	//卸载模块
	void UnRegisterMoudle(Moudle* moudle);
	template<class T>
	inline void UNRegisterMoudle()
	{
		UnRegisterMoudle(&T::getInstance());
	}
private:
	std::vector<Moudle*> m_MoudleVec{};
};
