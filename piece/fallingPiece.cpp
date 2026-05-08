#include "fallingPiece.h"
using namespace std;

FallingPiece::FallingPiece(const Piece& setPiece) :
    piece(setPiece),
    x(0),
    y(0) {}

Piece FallingPiece::getPiece() {
    return piece;
}
int FallingPiece::getX() {
    return x;
}
int FallingPiece::getY() {
    return y;
}

void FallingPiece::setPiece(const Piece& newPiece) {
    piece = newPiece;
}
void FallingPiece::setX(int newX) {
    x = newX;
}
void FallingPiece::setY(int newY) {
    y = newY;
}

void FallingPiece::invertBits() {
    for(auto& row : piece.getRowsRef()){
        for(size_t i = 0; i < row.size(); i++){
            row[i] = !row[i];
        }
    }
}

