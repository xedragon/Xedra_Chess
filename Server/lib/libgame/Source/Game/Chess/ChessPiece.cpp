#include "ChessPiece.h"

bool ChessPiece::NerverMove()
{
	return tracks.size() == 1;
}

void ChessPiece::AddTrack(int turn, int x, int y)
{
	tracks.push_back(std::make_tuple(turn, x, y));
}

void ChessPiece::PopTrack()
{
	tracks.pop_back();
}

int ChessPiece::Posid()
{
	return Pos2ID(posx,posy);
}

int Pos2ID(int posx, int posy)
{
	return (posy - 1) * 8 + posx;;
}
