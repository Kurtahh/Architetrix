#include "GameLoop.h"
#include "../piece/PieceController.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

// Gravity runs in a background thread; input runs in the main thread.
// A shared atomic flag signals when to stop.

static std::atomic<bool> gRunning{false};

GameLoop::GameLoop() {
    pieceController_ = new PieceController();
}

GameLoop::~GameLoop() { 
    delete pieceController_; 
}

void GameLoop::init() {
    std::cout << "Controls:\n"
              << "  a   - move left\n"
              << "  d   - move right\n"
              << "  SPC - hard drop\n"
              << "  i   - invert piece bits\n"
              << "  h   - hold/swap piece\n"
              << "  q   - quit\n\n";

    // Start with 4 rows at the bottom; rest is empty space
    for (int i = 0; i < 4; ++i)
        board_.addRowAtBottom(rowGenerator_.generate(level_));

    pieceController_->spawnNext();
    running_ = true;
    gRunning.store(true);
    lastRowAddTime_ = std::chrono::system_clock::now();
}

void GameLoop::run() {
    // Gravity thread: advances piece down on a timer and checks for row additions
    std::thread gravThread([this]() {
        while (gRunning.load()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(gravityMs()));
            if (state_ == GameState::FALLING) {
                tick();
                checkAndAddRow();
            }
        }
    });

    // Main thread: input loop
    renderer_.draw(board_,
                   pieceController_->getFallingPiece(),
                   pieceController_->getUpcomingPiece(),
                   pieceController_->getHeldPiece(),
                   score_, level_, getRowAddTimeRemainingMs());

    while (running_) {
        Action action = inputReader_.readInput();

        if (action == Action::QUIT) {
            endGame();
            break;
        }

        handleInput(action);
        renderer_.draw(board_,
                       pieceController_->getFallingPiece(),
                       pieceController_->getUpcomingPiece(),
                       pieceController_->getHeldPiece(),
                       score_, level_, getRowAddTimeRemainingMs());
    }

    gRunning.store(false);
    gravThread.join();
    std::cout << "\nGame over! Final score: " << score_ << "\n";
}

void GameLoop::handleInput(Action action) {
    if (state_ != GameState::FALLING) 
        return;

    switch (action) {
        case Action::MOVE_LEFT:  
            pieceController_->moveLeft();   
            break;
        case Action::MOVE_RIGHT: 
            pieceController_->moveRight();  
            break;
        case Action::HARD_DROP:  
            pieceController_->hardDrop(board_); 
            applyCollision(); 
            break;
        case Action::INVERT:     
            pieceController_->invertBits(); 
            break;
        case Action::HOLD_SWAP:  
            pieceController_->holdSwap();   
            break;
        default: 
            break;
    }
}

void GameLoop::tick() {
    // Move piece down one row
    pieceController_->stepDown();

    // Check if it has landed
    const FallingPiece* fp = pieceController_->getFallingPiece();

    if (fp && collisionChecker_.hasLanded(board_, *fp)) {
        state_ = GameState::COLLIDING;
        applyCollision();
    }

    renderer_.draw(board_,
                   pieceController_->getFallingPiece(),
                   pieceController_->getUpcomingPiece(),
                   pieceController_->getHeldPiece(),
                   score_, level_, getRowAddTimeRemainingMs());
}

void GameLoop::applyCollision() {
    const FallingPiece* fp = pieceController_->getFallingPiece();

    if (!fp) 
        return;

    bitwiseEngine_.applyPieceToBoard(board_, *fp);

    auto clearResult = eliminationChecker_.checkAndClear(board_);
    score_ += clearResult.scoreGained;

    if (board_.isOverflowed()) {
        endGame();
        return;
    }

    checkLevelUp();
    spawnNewPiece();
    state_ = GameState::FALLING;
}

void GameLoop::spawnNewPiece() {
    pieceController_->spawnNext();
}

void GameLoop::checkLevelUp() {
    int newLevel = (score_ / LEVEL_THRESHOLD) + 1;
    if (newLevel > level_) {
        level_ = newLevel;
        state_ = GameState::NEW_LEVEL;
        // Brief pause / visual cue could go here
        state_ = GameState::FALLING;
    }
}

void GameLoop::endGame() {
    running_ = false;
    gRunning.store(false);
    state_ = GameState::GAME_ENDED;
}

int GameLoop::getScore() const { 
    return score_; 
}

int GameLoop::getLevel() const { 
    return level_; 
}

GameState GameLoop::getGameState() const { 
    return state_; 
}

int GameLoop::gravityMs() const {
    // 500ms at level 1, floors at 100ms
    int ms = 500 - (level_ - 1) * 40;
    return ms < 100 ? 100 : ms;
}

int GameLoop::rowAddIntervalMs() const {
    // 6000ms (6 seconds) at level 1, decreases by 300ms per level, floors at 1000ms (1 second)
    int ms = 6000 - (level_ - 1) * 300;
    return ms < 1000 ? 1000 : ms;
}

void GameLoop::checkAndAddRow() {
    auto now = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
        now - lastRowAddTime_
    ).count();

    if (elapsed >= rowAddIntervalMs()) {
        board_.addRowAtBottom(rowGenerator_.generate(level_));
        lastRowAddTime_ = now;

        if (board_.isOverflowed()) {
            endGame();
        }
    }
}

int GameLoop::getRowAddTimeRemainingMs() const {
    auto now = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
        now - lastRowAddTime_
    ).count();
    
    int remaining = rowAddIntervalMs() - elapsed;
    return remaining > 0 ? remaining : 0;
}