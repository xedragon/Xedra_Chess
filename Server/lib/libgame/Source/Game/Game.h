#pragma once
#include <iostream>

class Game
{
public:
	virtual bool Init()=0;
	virtual bool Start()=0;
	virtual bool Shut()=0;
};