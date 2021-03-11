#pragma once
#include <iostream>
#include <vector>

class Moudle;

class Facade
{
public:
	static Facade& getInstance();
public:
	bool Init();
	bool Update();
	
	void Start();
public:
	void RegisterMoudle(Moudle* moudle);
private:
	std::vector<Moudle*> m_MoudleVec{};
};
