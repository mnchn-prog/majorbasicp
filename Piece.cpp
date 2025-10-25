#include "Piece.h"

bool Piece::MovePos(File x, Rank y, Cell(&board)[Rank::Ranksize][File::Filesize], Piece*& capturedPiece)
{
	if (!isMoveable(x, y, board)) { cout << "유효하지 않은 이동" << endl; system("pause"); return false; }

	if(board[y][x].currentPiece != PieceType::typeNone)
	{
		capturedPiece = board[y][x].pPiece;
		cout << capturedPiece;
	}
	pos.x = x;
	pos.y = y;
	return true;
}