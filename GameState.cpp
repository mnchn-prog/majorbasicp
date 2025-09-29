#include "GameState.h"

Piece* GameState::getPieceInBoard(File file, Rank rank) const
{
    for(Piece* p : pieces)
    {
        if (p == nullptr) continue;
        Position pos = p->GetPos();
        if (pos.x == file && pos.y == rank) return p;
    }
    return nullptr;
}

