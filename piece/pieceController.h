#ifndef PIECECONTROLLER_H
#define PIECECONTROLLER_H

#include <deque>
#include <optional>
#include "fallingPiece.h"
#include "pieceLoader.h"

class Board;

enum class Action {
    MOVE_LEFT,
    MOVE_RIGHT,
    DROP,
    HOLD,
    INVERT
};

class PieceController {
    FallingPiece falling;
    FallingPiece prevFalling;
    std::optional<Piece> held;
    std::deque<Piece> upcoming;
    const PieceLoader& loader;
    int difficulty;
    bool hasHeld;

    void dropFalling(const Board& board);
    void holdFalling();

    public:
    PieceController(const PieceLoader& loader);

    FallingPiece getFalling();
    std::optional<Piece> getHeld();
    std::deque<Piece> getUpcoming();
    int getDifficulty();
    void setDifficulty(int newDiff);
    
    void resolveInput(Action action, const Board& board);
};

#endif