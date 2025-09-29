#pragma once
#include "GameState.h"
#include "Cell.h"
class Game
{
private:
	GameState* whiteState, * blackState;
	Player turn;
	char images[12] = { 'N', };
	Cell (&board)[Rank::Ranksize][File::Filesize];
public:
	Game(Cell (&board)[8][8], GameState* ws, GameState* bs, Player turn) : board(board), whiteState(ws), blackState(bs), turn(turn) {}
	string unicodeForPiece(Player color, PieceType p) const;
    void MovePiece(string startPos, string endPos);
	void ShowBoard() const;
	void RefreshBoard();

};