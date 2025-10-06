#include "Piece.h"

void Piece::MovePos(File x, Rank y, Cell(&board)[Rank::Ranksize][File::Filesize])
{
	if (!isMoveable(x, y, board)) { cout << "유효하지 않은 이동" << endl; system("pause"); return; }
	pos.x = x;
	pos.y = y;
}