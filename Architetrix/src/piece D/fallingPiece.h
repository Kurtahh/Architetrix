#ifndef FALLINGPIECE_H
#define FALLINGPIECE_H

#include <vector>
#include "piece.h"

class FallingPiece {
    Piece piece;
    int x;
    int y;

    public:
    FallingPiece(const Piece& setPiece); //initializes x and y to 0 (idk what we should initialize them to rn cuz that depends on board logic)

    Piece getPiece() const; //standard  getters and setters for each field
    int getX() const;
    int getY() const;
    void setPiece(const Piece& newPiece); 
    void setX(int newX);
    void setY(int newY);

    void invertBits(); //calls piece.getRowsRef() to flip each bit in piece
};

#endif