#pragma once
#include "Piece.h"

class Rook: public Piece
{
private:
	const int dx[28] = { -1, -2, -3, -4, -5, -6, -7, 1, 2, 3, 4, 5, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	const int dy[28] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, -1, -2, -3, -4, -5, -6, -7 };
	bool isMoveable(File x, Rank y, Cell(&board)[Rank::Ranksize][File::Filesize]) const override;

public:
	Rook(File x, Rank y, PieceType type, Player color) : Piece(x, y, type, color) {}
	vector<pair<int, int>> CheckAttackCell(Cell(&board)[Rank::Ranksize][File::Filesize]) const override;

};