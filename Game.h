#pragma once
#include "Cell.h"
#include "GameState.h"

class Game
{
private:
	GameState* whiteState, * blackState;
	Player turn;
	Cell (&board)[Rank::Ranksize][File::Filesize];
	void RemovePiece(Piece* capturedPiece, Player color);
public:
	Game(Cell (&board)[8][8], GameState* ws, GameState* bs, Player turn) : board(board), whiteState(ws), blackState(bs), turn(turn) {}
	string unicodeForPiece(Player color, PieceType p) const;
    //void MovePiece(string startPos, string endPos); // 기획서랑 똑같게 하려면 고쳐야됨
	Piece* SelectStartPos(File startX, Rank startY);
	bool SelectEndPos(Piece* currentPiece, File startX, Rank startY);
	void ShowBoard() const;
	void RefreshBoard();
	inline Player GetTrun() const {return turn;}
};