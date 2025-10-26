#pragma once
#include <iostream>
#include "enum.h"

class Piece;

struct Cell
{
public:
	PieceType currentPiece;
	Player pieceColor;
	Piece* pPiece;
	bool AttackedByBlack,AttackedByWhite;
	Cell() : pieceColor(Player::playerNone), currentPiece(PieceType::typeNone), AttackedByBlack(false), AttckedByWhite(false), pPiece(nullptr) {}
	Cell(Player color, PieceType piece, bool ABB, bool ABW, Piece* pPiece) : pieceColor(color), currentPiece(piece), AttackedByBlack(ABB), AttckedByWhite(ABW), pPiece(pPiece) {};	
};
