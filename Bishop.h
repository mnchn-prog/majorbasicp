// Bishop.h (수정)

#pragma once
#include "Piece.h"

class Bishop: public Piece
{
private:
    // ⭐️ 4방향 (우상, 좌상, 우하, 좌하)만 정의
	const int dx[4] = { 1, -1, 1, -1 }; 
	const int dy[4] = { 1, 1, -1, -1 };
	
	bool isMoveable(File x, Rank y, Cell(&board)[Rank::Ranksize][File::Filesize]) const override;
public:
	Bishop(File x, Rank y, PieceType type, Player color) : Piece(x, y, type, color) {}
	vector<pair<int,int>> CheckAttackCell(Cell(&board)[Rank::Ranksize][File::Filesize]) const override;
};