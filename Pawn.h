#pragma once
#include "Piece.h"

class Pawn: public Piece
{
private:

   bool isMoveable(File x, Rank y, Cell(&board)[Rank::Ranksize][File::Filesize]) const override;

public:
   Pawn(File x, Rank y, PieceType type, Player color) : Piece(x, y, type, color) {}
   vector<pair<int, int>> CheckAttackCell(Cell(&board)[Rank::Ranksize][File::Filesize]) const override;

};


#include "Pawn.h"

