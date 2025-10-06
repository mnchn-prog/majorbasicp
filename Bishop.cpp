#include "Bishop.h"

bool Bishop::isMoveable(File x, Rank y, Cell(&board)[Rank::Ranksize][File::Filesize]) const
{
	for (int i = 0; i < 14; i++)
	{
		int nextX = pos.x + dx[i];
		int nextY = pos.y + dy[i];
		if(nextX < 0 || nextX >= File::Filesize || nextY < 0 || nextY >= Rank::Ranksize) //범위 벗어나면
		{
			if(i < 7) // -체크할 때 범위 넘어가면 + 체크 시작
			{
				i = 6;
				continue;
			}
			else // false 리턴
			{
				return false;
			}
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
			if(i < 7) // -부분 체크 중이라면
			{
				i = 6; // + 부분 체크로 넘어가기
				continue;
			}
			else // +부분 체크 중이라면
			{
				return false; 
			}
		}
		else // 상대 기물이 막을 때
		{
			if (nextX == x && nextY == y) // 목표 좌표라면
			{
				return true;
			}
			else // 더 먼 칸 체크할 수 없으니 넘어가기
			{
				if(i < 7)
				{
					i = 6;
					continue;
				}
				else
				{
					return false;
				}
			}
		}
		if (i == 13) // 마지막까지 좌표 못찾았을 때
			return false;
	}

	if (board[y][x].currentPiece != PieceType::typeNone && board[y][x].pieceColor == color) return false;
	return true;
}



vector<pair<int,int>> Bishop::CheckAttackCell(Cell(&board)[Rank::Ranksize][File::Filesize]) const
{
	vector<pair<int, int>> attackPos;
	for (int i = 0; i < 14; i++)
	{
		int attackX = pos.x + dx[i];
		int attackY = pos.y + dy[i];
		if(attackX < 0 || attackX >= File::Filesize || attackY < 0 || attackY >= Rank::Ranksize) //범위 벗어나면
		{
			if(i < 7) // -체크할 때 범위 넘어가면 + 체크 시작
			{
				i = 6;
				continue;
			}
			else // break(더 체크할 범위 없음)
			{
				break;
			}
		}

		if(board[attackY][attackX].pieceColor == Player::playerNone) // 막는 기물 없을 때
		{
			attackPos.push_back({attackX, attackY});
		}

		else // 기물이 있을 때
		{
			attackPos.push_back({attackX, attackY});
			if(i < 7) // -부분 체크 중이라면
			{
				i = 6; // + 부분 체크로 넘어가기
				continue;
			}
			else // +부분 체크 중이라면
			{
				break; 
			}
		}
	}
	return attackPos;
}