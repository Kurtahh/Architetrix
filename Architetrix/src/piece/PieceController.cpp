#include "PieceController.h"
#include "../board/Board.h"
#include <cstdlib>
#include <stdexcept>
#include <random>

PieceController::PieceController() {
    loader_.loadPieces();
    refillQueue(3);
}

// ── Spawn ─────────────────────────────────────────────────────────────────────

void PieceController::spawnNext() {
    refillQueue(3);
    const Piece* next = upcoming_.front();
    upcoming_.pop_front();
    spawnPiece(next);
    holdUsedThisPiece_ = false;
}

void PieceController::spawnPiece(const Piece* piece) {
    // Spawn centred at the top of the board
    int startCol = (Board::WIDTH / 2) - (piece->getWidth() / 2);
    fallingPiece_ = std::make_unique<FallingPiece>(piece, startCol, 0);
}

void PieceController::setLevel(int level) {
    currentLevel_ = level;
}

// ── Movement ─────────────────────────────────────────────────────────────────

void PieceController::moveLeft() { 
    if (fallingPiece_) 
        fallingPiece_->moveLeft();  
}

void PieceController::moveRight() { 
    if (fallingPiece_) 
        fallingPiece_->moveRight(); 
}

void PieceController::stepDown() { 
    if (fallingPiece_) 
        fallingPiece_->stepDown();
}

void PieceController::invertBits() { 
    if (fallingPiece_) 
        fallingPiece_->invertBits();
}

void PieceController::hardDrop(const Board& board) {
    if (fallingPiece_) 
        fallingPiece_->hardDrop(board);
}

void PieceController::holdSwap() {
    if (holdUsedThisPiece_) 
        return;  // only once per piece
    holdUsedThisPiece_ = true;

    const Piece* current = fallingPiece_ ? fallingPiece_->getPiece() : nullptr;

    if (heldPiece_) {
        //swap: spawn the held piece, hold the current one
        const Piece* toSpawn = heldPiece_;
        heldPiece_ = current;
        spawnPiece(toSpawn);
    } else {
        //nothing held yet: stash current, spawn next from queue
        heldPiece_ = current;
        refillQueue(1);
        const Piece* next = upcoming_.front();
        upcoming_.pop_front();
        spawnPiece(next);
    }
}

const FallingPiece* PieceController::getFallingPiece() const { 
    return fallingPiece_.get(); 
}

const Piece* PieceController::getHeldPiece() const { 
    return heldPiece_; 
}

const Piece* PieceController::getUpcomingPiece() const {
    return upcoming_.empty() ? nullptr : upcoming_.front();
}

void PieceController::refillQueue(int n) {
    while (static_cast<int>(upcoming_.size()) < n)
        upcoming_.push_back(pickRandom());
}

const Piece* PieceController::pickRandom() const {
    // Map level to difficulty: 1=easy, 2-3=medium, 4+=hard
    int difficulty = 1;  // default to easy
    if (currentLevel_ >= 2)
        difficulty = 2;  // medium starting at level 2
    if (currentLevel_ >= 4)
        difficulty = 3;  // hard starting at level 4
    
    static std::mt19937 rng(std::random_device{}());
    
    const std::vector<Piece>& pool = 
        difficulty == 1 ? loader_.getEasy() :
        difficulty == 2 ? loader_.getMedium() :
        loader_.getHard();
    
    if (pool.empty()) 
        return nullptr;
    
    std::uniform_int_distribution<int> dist(0, pool.size() - 1);
    return &pool[dist(rng)];
}

void PieceController::resolveInput(Action action, const Board& board) {
    switch (action) {
        case Action::MOVE_LEFT:
            moveLeft();
            break;
        case Action::MOVE_RIGHT:
            moveRight();
            break;
        case Action::HARD_DROP:
            hardDrop(board);
            break;
        case Action::HOLD_SWAP:
            holdSwap();
            break;
        case Action::INVERT:
            invertBits();
            break;
        case Action::QUIT:
        case Action::NONE:
            //do nothing for QUIT and NONE
            break;
    }
}