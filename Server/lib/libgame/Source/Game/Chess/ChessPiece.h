#pragma once
#include <vector>
#include <tuple>

int Pos2ID(int posx, int posy);

class ChessPiece
{
public:
	int id;
	int color;
	int type;
	int posx;
	int posy;
private:
	std::vector<std::tuple<int/*turn*/, int, int>> tracks{};
public:
	bool NerverMove();

	void AddTrack(int turn, int x, int y);
	void PopTrack();

	int Posid();
};

