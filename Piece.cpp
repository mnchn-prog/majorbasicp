#include "Piece.h"

bool Piece::MovePos(File x, Rank y, Cell(&board)[Rank::Ranksize][File::Filesize], Piece*& capturedPiece)
{
	if (!isMoveable(x, y, board)) { cout << "유효하지 않은 이동" << endl; system("pause"); return false; }

	if(board[y][x].currentPiece != PieceType::typeNone)
	{
		capturedPiece = board[y][x].pPiece;
		cout << capturedPiece;
		system("pause");
	}
	pos.x = x;
	pos.y = y;
	if (capturedPiece != nullptr) {
    std::cout << "DEBUG: MovePos에서 capturedPiece는 nullptr이 아닙니다. ";
    system("pause");
}
	return true;
}