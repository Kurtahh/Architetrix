#include "CollisionChecker.h"
#include "../board/Board.h"  
#include "../piece/FallingPiece.h"

bool CollisionChecker::isCollision(const Board& board, const FallingPiece& piece) const {
    (void)board;

    const auto& pieceBits = piece.getBits();

    for (int i = 0; i < static_cast<int>(pieceBits.size()); ++i) {
        int col = piece.getCol() + i;
        if (col < 0 || col >= Board::WIDTH) 
            return true;
    }

    if (piece.getRow() >= Board::VISIBLE_HEIGHT) 
        return true;
        
    return false;
}

bool CollisionChecker::hasLanded(const Board& board, const FallingPiece& piece) const {
    // Stack top in visible coordinates: empty rows sit above it.
    // rows_[0] is drawn at visible row = VISIBLE_HEIGHT - getHeight()
    int stackTop = Board::VISIBLE_HEIGHT - board.getHeight();
    // Piece lands when it reaches the row just above the stack,
    // or when it hits the very bottom of the screen (no stack at all).
    return piece.getRow() >= stackTop;
}