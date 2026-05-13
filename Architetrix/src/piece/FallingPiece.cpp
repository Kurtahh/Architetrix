#include "FallingPiece.h"
#include "../board/Board.h"

FallingPiece::FallingPiece(const Piece* piece, int startCol, int startRow)
    : piece_(piece), col_(startCol), row_(startRow)
{
    if (piece_ && !piece_->getBits2D().empty())
        bits_ = piece_->getBits2D()[0];
}

int FallingPiece::getRow() const { 
    return row_; 
}

int FallingPiece::getCol() const { 
    return col_; 
}

const std::vector<bool>& FallingPiece::getBits() const { 
    return bits_; 
}

const Piece* FallingPiece::getPiece() const { 
    return piece_; 
}

void FallingPiece::moveLeft() { 
    if (col_ > 0) 
        --col_; 
}

void FallingPiece::moveRight() { 
    ++col_; 
}

void FallingPiece::stepDown() { 
    ++row_; 
}

void FallingPiece::invertBits() {
    if (piece_) {
        auto& rows = const_cast<Piece*>(piece_)->getRowsRef();
        for (auto& row : rows) {
            for (size_t i = 0; i < row.size(); i++) {
                row[i] = !row[i];
            }
        }

        if (!rows.empty()) {
            bits_ = rows[0];
        }
    }
}

void FallingPiece::hardDrop(const Board& board) {
    int stackTop = Board::VISIBLE_HEIGHT - board.getHeight();
    row_ = stackTop;
}