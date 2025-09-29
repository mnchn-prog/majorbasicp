#include "Bishop.h"

bool Bishop::isMoveable(File x, Rank y, Cell(&board)[Rank::Ranksize][File::Filesize]) const
{
	int curX = static_cast<int>(pos.x);
	int curY = static_cast<int>(pos.y);
	
	for (int i = 0; i < 8; i++)
	{
		int nextX = curX + dx[i];
		int nextY = curY + dy[i];

		if (nextX == static_cast<int>(x) && nextY == static_cast<int>(y))
		{
			break;
		}
		if (i == 7)
			return false;
	}

	if (board[y][x].currentPiece != PieceType::typeNone && board[y][x].pieceColor == color) return false;
	return true;
}

void Bishop::MovePos(File x, Rank y, Cell(&board)[Rank::Ranksize][File::Filesize])
{
	//if (!isMoveable(x, y, board)) { /*cout << "유효하지 않은 이동" << endl;*/ system("pause"); return; }
	pos.x = x;
	pos.y = y;
}
