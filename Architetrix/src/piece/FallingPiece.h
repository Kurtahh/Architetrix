#ifndef FALLING_PIECE_H_434345
#define FALLING_PIECE_H_434345

#include "Piece.h"
#include <vector>

class Board; //forward declaration so compiler doesn't freak out

class FallingPiece {
    const Piece* piece_;
    int col_;
    int row_;
    std::vector<bool> bits_;

    public:
    FallingPiece(const Piece* piece, int startCol, int startRow = 0);

    //position on the board grid
    int getRow() const;
    int getCol() const;

    //bit values of the piece
    const std::vector<bool>& getBits() const;

    //movement methods for the piece
    void moveLeft();
    void moveRight();
    void stepDown();

    //flips all bits (NOT operation)
    void invertBits();

    //drops the piece on the current columns instantly
    void hardDrop(const Board& board);

    const Piece* getPiece() const;
};

#endif