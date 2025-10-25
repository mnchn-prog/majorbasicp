// Queen.h

#pragma once
#include "Piece.h"

class Queen: public Piece
{
private:
	const int dx[8] = { 0, 0, -1, 1, 1, -1, 1, -1 }; 
	const int dy[8] = { 1, -1, 0, 0, 1, 1, -1, -1 };
    
	bool isMoveable(File x, Rank y, Cell(&board)[Rank::Ranksize][File::Filesize]) const override;

public:
	Queen(File x, Rank y, PieceType type, Player color) : Piece(x, y, type, color) {}
	vector<pair<int, int>> CheckAttackCell(Cell(&board)[Rank::Ranksize][File::Filesize]) const override;

};