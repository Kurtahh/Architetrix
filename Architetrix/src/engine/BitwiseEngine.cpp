#include "BitwiseEngine.h"
#include "../piece/FallingPiece.h"

void BitwiseEngine::applyPieceToBoard(Board& board, const FallingPiece& piece) const {
    // Convert visible-coordinate row to stack index.
    // rows_[0] is drawn at visible row = VISIBLE_HEIGHT - getHeight()
    int stackTop  = Board::VISIBLE_HEIGHT - board.getHeight();
    int stackIndex = piece.getRow() - stackTop;

    if (stackIndex < 0 || stackIndex >= board.getHeight()) 
        return;

    int pieceCol = piece.getCol();
    const auto& pieceBits = piece.getBits();

    auto& row = board.getRows()[stackIndex];
    
    for (int i = 0; i < static_cast<int>(pieceBits.size()); ++i) {
        int col = pieceCol + i;
        if (col < 0 || col >= Board::WIDTH) 
            continue;
        if (col >= static_cast<int>(row.bits.size())) 
            continue;

        row.bits[col] = applyOp(pieceBits[i], row.bits[col], row.op);
    }
}

bool BitwiseEngine::applyOp(bool pieceBit, bool boardBit, Board::Operator op) const {
    switch (op) {
        case Board::Operator::AND:  
            return pieceBit && boardBit;
        case Board::Operator::OR:   
            return pieceBit || boardBit;
        case Board::Operator::XOR:  
            return pieceBit != boardBit;
        case Board::Operator::NAND: 
            return !(pieceBit && boardBit);
        case Board::Operator::NOR:  
            return !(pieceBit || boardBit);
        default: 
            return boardBit;
    }
}