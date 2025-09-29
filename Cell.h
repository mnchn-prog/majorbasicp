#pragma once
#include <iostream>
#include "enum.h"

struct Cell
{
public:
	PieceType currentPiece;
	Player pieceColor;
	bool AttackedByBlack,AttckedByWhite;
	Cell() : pieceColor(Player::playerNone), currentPiece(PieceType::typeNone), AttackedByBlack(false), AttckedByWhite(false) {}
	Cell(Player color, PieceType piece, bool ABB, bool ABW) : pieceColor(color), currentPiece(piece), AttackedByBlack(ABB), AttckedByWhite(ABW) {};
};