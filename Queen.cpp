#include "Queen.h"


// Queen.cpp / Queen::isMoveable

bool Queen::isMoveable(File x, Rank y, Cell(&board)[Rank::Ranksize][File::Filesize]) const
{
	int curX = static_cast<int>(pos.x);
	int curY = static_cast<int>(pos.y);
    int targetX = static_cast<int>(x);
    int targetY = static_cast<int>(y);
    
    // 8방향 탐색
	for (int dir = 0; dir < 8; ++dir)
	{
        // 각 방향으로 최대 7칸까지 이동하며 검사
		for (int dist = 1; dist < 8; ++dist)
		{
			int nextX = curX + dx[dir] * dist;
			int nextY = curY + dy[dir] * dist;

            // 1. 범위 벗어나면 이 방향 탐색 종료
			if (nextX < 0 || nextX >= File::Filesize || nextY < 0 || nextY >= Rank::Ranksize) {
				break;
			}
            
            // 2. 목표 좌표에 도달했는지 확인
			if (nextX == targetX && nextY == targetY)
			{
                // 목표 칸에 내 기물이 있으면 이동 불가
				if (board[targetY][targetX].pieceColor == color) return false;
                
                // 내 기물이 없으면 (빈 칸 또는 상대 기물) 이동 가능
				return true; 
			}

            // 3. 목표 전에 기물이 있는지 확인 (경로 막힘 검사)
			if (board[nextY][nextX].currentPiece != PieceType::typeNone)
			{
                // 목표 지점 전에 기물이 막고 있으므로, 이 방향 탐색 종료
				break;
			}
		}
	}

	// 모든 경로를 탐색했으나 목표 좌표를 찾지 못했거나 유효하지 않은 이동인 경우
	return false;
}

// Queen.cpp / Queen::CheckAttackCell

vector<pair<int, int>> Queen::CheckAttackCell(Cell(&board)[Rank::Ranksize][File::Filesize]) const
{
	vector<pair<int, int>> attackPos;
	int curX = static_cast<int>(pos.x);
	int curY = static_cast<int>(pos.y);

    // 8방향 탐색
	for (int dir = 0; dir < 8; ++dir)
	{
        // 각 방향으로 최대 7칸까지 이동하며 검사
		for (int dist = 1; dist < 8; ++dist)
		{
			int attackX = curX + dx[dir] * dist;
			int attackY = curY + dy[dir] * dist;
            
            // 1. 범위 벗어나면 이 방향 탐색 종료
			if (attackX < 0 || attackX >= File::Filesize || attackY < 0 || attackY >= Rank::Ranksize) {
				break;
			}
            
            // 2. 공격 칸 추가
			attackPos.push_back({attackX, attackY});

            // 3. 기물에 막히는지 확인
			if (board[attackY][attackX].currentPiece != PieceType::typeNone)
			{
                // 아군 기물이든 적군 기물이든 막고 있다면 이 방향 탐색 종료
				break;
			}
		}
	}
	return attackPos;
}