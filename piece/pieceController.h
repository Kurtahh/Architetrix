#ifndef PIECECONTROLLER_H
#define PIECECONTROLLER_H

#include <vector>
#include "fallingPiece.h"

class PieceController {
    FallingPiece falling;
    const Piece held;
    std::vector<Piece> upcoming;

    public:
    FallingPiece getFalling();
    Piece getHeld();
    std::vector<Piece> getUpcoming();
};

#endif