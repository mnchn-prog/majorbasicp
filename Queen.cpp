#include "Queen.h"


bool Queen::isMoveable(File x, Rank y, Cell(&board)[Rank::Ranksize][File::Filesize]) const
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

vector<pair<int,int>> Queen::CheckAttackCell(Cell(&board)[Rank::Ranksize][File::Filesize]) const
{
	vector<pair<int,int>> re{{1, 1}};
	return re;
}