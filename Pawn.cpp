#include "Pawn.h"

bool Pawn::isMoveable(File x, Rank y, Cell(&board)[Rank::Ranksize][File::Filesize]) const
{
    int curX = static_cast<int>(pos.x);
    int curY = static_cast<int>(pos.y);
    int targetX = static_cast<int>(x);
    int targetY = static_cast<int>(y);

    int dir = (color == Player::white) ? 1 : -1; // 흰색은 (y값이) +만 , 검정은 -만 가능
    int startRow = (color == Player::white) ? 1 : 6; // 초기 위치
    int lastRow = (color == Player::white) ? 7 : 0;  // 이동 불가 랭크

    if (curY == lastRow) return false;  // 마지막칸이면 못감

    // 1칸 이동 가능한지
    if (targetX == curX && targetY == curY + dir) {
        if (board[targetY][targetX].currentPiece == PieceType::typeNone)
            return true;
    }

    // 처음 이동 시 2칸 이동 가능
    if (targetX == curX && targetY == curY + 2 * dir) {
        if (curY == startRow &&
            board[curY + dir][curX].currentPiece == PieceType::typeNone &&
            board[targetY][targetX].currentPiece == PieceType::typeNone)
            return true;
    }

    // 대각선 공격 가능한지
    if ((targetX == curX + 1 || targetX == curX - 1) && targetY == curY + dir) {
        if (board[targetY][targetX].currentPiece != PieceType::typeNone &&
            board[targetY][targetX].pieceColor != color)
            return true;
    }

    return false; // 그 외 이동 불가
}

vector<pair<int, int>> Pawn::CheckAttackCell(Cell(&board)[Rank::Ranksize][File::Filesize]) const
{
    vector<pair<int, int>> attackCells;
    int curX = static_cast<int>(pos.x);
    int curY = static_cast<int>(pos.y);
    int dir = (color == Player::white) ? 1 : -1;

    // 대각선 좌측 공격
    if (curX > 0 && curY + dir >= 0 && curY + dir < Rank::Ranksize)
        attackCells.push_back({ curX - 1, curY + dir });

    // 대각선 우측 공격
    if (curX < File::Filesize - 1 && curY + dir >= 0 && curY + dir < Rank::Ranksize)
        attackCells.push_back({ curX + 1, curY + dir });

    return attackCells;
}
