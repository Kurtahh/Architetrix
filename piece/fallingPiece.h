#ifndef FALLINGPIECE_H
#define FALLINGPIECE_H

#include <vector>
#include "piece.h"

class FallingPiece {
    Piece piece;
    int x;
    int y;

    public:
    FallingPiece(const Piece& setPiece);

    Piece getPiece();
    int getX();
    int getY();
    void setPiece(const Piece& newPiece);
    void setX(int newX);
    void setY(int newY);

    void invertBits();
};

#endif