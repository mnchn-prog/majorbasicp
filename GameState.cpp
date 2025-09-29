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

string unicodeForPiece(Player color, char p){

    if(color == Player::black)
    {
        switch(p){

            case 'K': return "♚"; case 'Q': return "♛"; case 'R': return "♜";
            case 'B': return "♝"; case 'N': return "♞"; case 'P': return "♟";
            default: return ".";
        }
    }
    else
    {
        switch(p){
            case 'K': return "♔"; case 'Q': return "♕"; case 'R': return "♖";
            case 'B': return "♗"; case 'N': return "♘"; case 'P': return "♙";
            default: return ".";
        }
    }
}