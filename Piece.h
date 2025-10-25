#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "enum.h"
#include "Cell.h"
using namespace std;

struct Position
{
	File x;
	Rank y;
};

class Piece
{
private:
	const PieceType type;
protected:
	Position pos;
	const Player color;
	virtual bool isMoveable(File x, Rank y, Cell(&board)[Rank::Ranksize][File::Filesize]) const = 0;

public:
	Piece(File x, Rank y, PieceType type, Player color) : pos{x, y}, type(type), color(color) {}
	PieceType GetType() const { return type; }
	Position GetPos() const { return pos; }
	bool MovePos(File x, Rank y, Cell(&board)[Rank::Ranksize][File::Filesize], Piece* capturedPiece);
	virtual vector<pair<int, int>> CheckAttackCell(Cell(&board)[Rank::Ranksize][File::Filesize]) const = 0;

};
