// Rook.h (수정)

#pragma once
#include "Piece.h"

class Rook: public Piece
{
private:
	const int dx[4] = { 0, 0, -1, 1 }; 
	const int dy[4] = { 1, -1, 0, 0 };
    
	bool isMoveable(File x, Rank y, Cell(&board)[Rank::Ranksize][File::Filesize]) const override;

public:
	Rook(File x, Rank y, PieceType type, Player color) : Piece(x, y, type, color) {}
	vector<pair<int, int>> CheckAttackCell(Cell(&board)[Rank::Ranksize][File::Filesize]) const override;

};