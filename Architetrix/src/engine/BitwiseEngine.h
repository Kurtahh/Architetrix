#ifndef BITWISE_ENGINE_H_821222
#define BITWISE_ENGINE_H_821222

#include "../board/Board.h"

/// Forward declaration (defined in your friend's module)
class FallingPiece;

/// Applies bitwise operations between a falling piece and board rows.
/// Does NOT handle clearing or operator generation — those live elsewhere.
class BitwiseEngine {
public:
    /// Apply the falling piece to the board at its current position.
    /// Modifies board in-place: for each cell the piece covers,
    /// applies row.op(pieceBit, rowBit) and writes result back.
    void applyPieceToBoard(Board& board, const FallingPiece& piece) const;

private:
    /// Applies a single bitwise operation between two bits.
    bool applyOp(bool pieceBit, bool boardBit, Board::Operator op) const;
};

#endif