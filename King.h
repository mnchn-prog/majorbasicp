#pragma once
#include "Piece.h"

class King: public Piece
{
private:
	const int dx[8] = { -2, -2, -1, -1, 1, 1, 2, 2 };
	const int dy[8] = { -1, 1, -2, 2, -2, 2, -1, 1 };
	bool isMoveable(File x, Rank y, Cell(&board)[Rank::Ranksize][File::Filesize]) const override;
public:
	King(File x, Rank y, PieceType type, Player color) : Piece(x, y, type, color) {}
	void MovePos(File x, Rank y, Cell(&board)[Rank::Ranksize][File::Filesize]) override;
};