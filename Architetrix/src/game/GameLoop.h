#ifndef GAME_LOOP_H_456234
#define GAME_LOOP_H_456234

#include "GameState.h"
#include "../board/Board.h"
#include "../board/RowGenerator.h"
#include "../engine/BitwiseEngine.h"
#include "../engine/CollisionChecker.h"
#include "../engine/EliminationChecker.h"
#include "../input/InputReader.h"
#include "../render/Renderer.h"

class PieceController;

class GameLoop {
public:
    GameLoop();
    ~GameLoop();

    /// Initialise board, spawn first piece, print instructions.
    void init();

    /// Blocking: runs until state == GAME_ENDED.
    void run();

    int getScore() const;
    int getLevel() const;
    GameState getGameState() const;

private:
    /// --- Internal tick helpers ---
    void handleInput(Action action);
    void tick(); // gravity + state transitions
    void applyCollision(); // bitwise merge + elimination
    void spawnNewPiece();
    void checkLevelUp();
    void endGame();

    Board board_;
    RowGenerator rowGenerator_;
    BitwiseEngine bitwiseEngine_;
    CollisionChecker collisionChecker_;
    EliminationChecker eliminationChecker_;
    InputReader inputReader_;
    Renderer renderer_;

    PieceController* pieceController_ = nullptr;

    // --- Game state ---
    GameState state_ = GameState::FALLING;
    int score_ = 0;
    int level_ = 1;

    bool running_ = false;
    int landingCount_ = 0;  // triggers new row every N landings TO CHANGE

    // Level-up threshold: every N points → level++
    static constexpr int LEVEL_THRESHOLD = 500;

    // Gravity interval in milliseconds (decreases with level)
    int gravityMs() const;
};

#endif