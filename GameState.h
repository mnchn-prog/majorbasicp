#pragma once

#include <iostream>
#include <vector>
#include "enum.h"
#include "Piece.h"

class GameState
{
private:
	vector<Piece*> pieces;
	Player player;
public:
	GameState(vector<Piece*> p, Player player) : player(player)
	{
        copy(p.begin(), p.end(), back_inserter(pieces));
	}

	Piece* getPieceInBoard(File file, Rank rank) const;
	vector<Piece*>& GetPieces() { return pieces; }
	~GameState();
};