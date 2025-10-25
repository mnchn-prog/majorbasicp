#include "King.h"

bool King::isMoveable(File x, Rank y, Cell(&board)[Rank::Ranksize][File::Filesize]) const
{
   int curX = static_cast<int>(pos.x);
   int curY = static_cast<int>(pos.y);

   int targetX = static_cast<int>(x);
   int targetY = static_cast<int>(y);
   
   for (int i = 0; i < 8; i++)
   {
      int nextX = curX + dx[i];
      int nextY = curY + dy[i];

      if (nextX == targetX && nextY == targetY)
      {
               
         if (board[targetY][targetX].currentPiece != PieceType::typeNone &&  // 우리팀 말 있는 곳인가
            board[targetY][targetX].pieceColor == color)
            return false;

         return true; // 이동하자~
      }
   }

   return false;
}

vector<pair<int, int>> King::CheckAttackCell(Cell(&board)[Rank::Ranksize][File::Filesize]) const
{
   vector<pair<int, int>> attackCells;

   int curX = static_cast<int>(pos.x);
   int curY = static_cast<int>(pos.y);

   for (int i = 0; i < 8; i++)
   {
      int nextX = curX + dx[i];
      int nextY = curY + dy[i];

      // 보드 안에 값인가
      if (nextX < 0 || nextX >= File::Filesize || nextY < 0 || nextY >= Rank::Ranksize)
         continue;

      // 우리팀 말이 있는 곳인가
      if (board[nextY][nextX].currentPiece != PieceType::typeNone &&
         board[nextY][nextX].pieceColor == color)
         continue;

      // 나머지들은 push_back으로 vector에 저장
      attackCells.push_back({ nextX, nextY });
   }

   return attackCells;
}
