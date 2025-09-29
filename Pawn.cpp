#include "Pawn.h"


bool Pawn::isMoveable(File x, Rank y, Cell(&board)[Rank::Ranksize][File::Filesize]) const
{
	int curX = static_cast<int>(pos.x);
	int curY = static_cast<int>(pos.y);
	
	if(curX != x) {cout << "잘못된 입력입니다."; system("pause"); return false;}
	if (board[y][x].currentPiece != PieceType::typeNone && board[y][x].pieceColor == color) return false;
	return true;
}

void Pawn::MovePos(File x, Rank y, Cell(&board)[Rank::Ranksize][File::Filesize])
{
	//if (!isMoveable(x, y, board)) { /*cout << "유효하지 않은 이동" << endl;*/ system("pause"); return; }
	pos.x = x;
	pos.y = y;
}
