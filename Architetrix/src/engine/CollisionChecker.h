#ifndef COLLISION_CHECKER_H_545466
#define COLLISION_CHECKER_H_545466

class Board;
class FallingPiece;

class CollisionChecker {
    public:
    /// Returns true if the piece at its current position would collide.
    bool isCollision(const Board& board, const FallingPiece& piece) const;

    /// Returns true if the piece has reached the last row (landed).
    bool hasLanded(const Board& board, const FallingPiece& piece) const;
};

#endif