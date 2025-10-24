#include "Rook.h"

bool Rook::isMoveable(File x, Rank y, Cell(&board)[Rank::Ranksize][File::Filesize]) const
{
	for (int i = 0; i < 28; i++)
	{
		int nextX = pos.x + dx[i];
		int nextY = pos.y + dy[i];
		if(nextX < 0 || nextX >= File::Filesize || nextY < 0 || nextY >= Rank::Ranksize) //범위 벗어나면
		{
			if(i < 7) i = 6;
			else if(i < 14) i = 13;
			else if(i < 21) i = 20;
			else break;
			continue;
		}
		if(board[nextY][nextX].pieceColor == Player::playerNone) // 막는 기물 없을 때
		{
			if (nextX == x && nextY == y) // 목표 좌표라면
			{
				return true;
			}
		}
		else if(board[nextY][nextX].currentPiece == color) // 내 기물이 막을 때
		{
			if(i < 7) i = 6;
			else if(i < 14) i = 13;
			else if(i < 21) i = 20;
			else break;
			continue;
		}
		else // 상대 기물이 막을 때
		{
			if (nextX == x && nextY == y) // 목표 좌표라면
			{
				return true;
			}
			else // 더 먼 칸 체크할 수 없으니 넘어가기
			{
				if(i < 7) i = 6;
				else if(i < 14) i = 13;
				else if(i < 21) i = 20;
				else break;
				continue;
			}
		}
		if (i == 27) // 마지막까지 좌표 못찾았을 때
			return false;
	}

	if (board[y][x].currentPiece != PieceType::typeNone && board[y][x].pieceColor == color) return false;
	return true;
}



vector<pair<int,int>> Rook::CheckAttackCell(Cell(&board)[Rank::Ranksize][File::Filesize]) const
{
	vector<pair<int, int>> attackPos;
	for (int i = 0; i < 14; i++)
	{
		int attackX = pos.x + dx[i];
		int attackY = pos.y + dy[i];
		if(attackX < 0 || attackX >= File::Filesize || attackY < 0 || attackY >= Rank::Ranksize) //범위 벗어나면
		{
			if(i < 7) i = 6;
			else if(i < 14) i = 13;
			else if(i < 21) i = 20;
			else break;
			continue;
		}

		if(board[attackY][attackX].pieceColor == Player::playerNone) // 막는 기물 없을 때
		{
			attackPos.push_back({attackX, attackY});
		}

		else // 기물이 있을 때
		{
			attackPos.push_back({attackX, attackY});
			if(i < 7) i = 6;
			else if(i < 14) i = 13;
			else if(i < 21) i = 20;
			else break;
			continue;
		}
	}
	return attackPos;
}