#pragma once

class Moudle
{
public:
	virtual bool Init() = 0;
	virtual bool Update() = 0;
	virtual bool Shut() = 0;
};