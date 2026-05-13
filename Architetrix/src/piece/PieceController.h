#ifndef PIECE_CONTROLLER_H_456778
#define PIECE_CONTROLLER_H_456778

#include "FallingPiece.h"
#include "PieceLoader.h"
#include "../input/InputReader.h"
#include <memory>
#include <deque>

class Board;

//owns and manages the falling piece, held piece, and upcoming-piece queue

class PieceController {
    PieceLoader loader_;

    std::unique_ptr<FallingPiece> fallingPiece_;
    const Piece* heldPiece_ = nullptr;
    std::deque<const Piece*> upcoming_;

    bool holdUsedThisPiece_ = false;  //hold is once-per-piece
    int currentLevel_ = 1;  // track current level for piece difficulty

    //pick a random piece based on level
    const Piece* pickRandom() const;

    //makes sure queue always has N members
    void refillQueue(int n = 3);

    //spawns parameter piece
    void spawnPiece(const Piece* piece);
    
    public:
    explicit PieceController(const std::string& piecesFile = "pieces.txt");

    //spawns the next piece from the upcoming queue (refills queue if needed)
    void spawnNext();

    //updates the current level for piece difficulty scaling
    void setLevel(int level);

    //movement is delegated to FallingPiece
    void moveLeft();
    void moveRight();
    void stepDown();
    void hardDrop(const Board& board);
    void invertBits();

    //hold/swap — swaps falling piece with held slot (works once per piece only)
    void holdSwap();

    //resolves input actions (from team member's implementation)
    void resolveInput(Action action, const Board& board);

    //getters used by GameLoop and Renderer
    const FallingPiece* getFallingPiece() const;
    const Piece* getUpcomingPiece() const;  //peek at next queued piece
    const Piece* getHeldPiece() const;
};

#endif