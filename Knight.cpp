#include "Knight.h"

bool Knight::isMoveable(File x, Rank y, Cell(&board)[Rank::Ranksize][File::Filesize]) const
{
	int curX = static_cast<int>(pos.x);
	int curY = static_cast<int>(pos.y);
	
	for (int i = 0; i < 8; i++)
	{
		int nextX = curX + dx[i];
		int nextY = curY + dy[i];
		if(board[nextY][nextX].pieceColor == color)
		{
			if(i == 7) return false;
			continue;
		}

		if (nextX == x && nextY == y)
		{
			break;
		}

		if (i == 7)
			return false;
	}

	return true;
}

vector<pair<int,int>> Knight::CheckAttackCell(Cell(&board)[Rank::Ranksize][File::Filesize]) const
{	
	vector<pair<int, int>> attackPos;
	for (int i = 0; i < 8; i++)
	{
		int attackX = pos.x + dx[i];
		int attackY = pos.y + dy[i];
		if(attackX < 0 || attackX >= File::Filesize || attackY < 0 || attackY >= Rank::Ranksize) continue;
		
		attackPos.push_back({attackX, attackY});
	}
	return attackPos;
}