#ifndef RENDERER_H_477211
#define RENDERER_H_477211

#include "../board/Board.h"
#include <string>

class FallingPiece;
class Piece;  // for held/upcoming

// Renderer owns no state — it reads const refs and writes to stdout each tick.
class Renderer {
    void drawBoard(const Board& board, const FallingPiece* piece) const;
    void drawSidebar(const Piece* upcoming, const Piece* held, int score, int level, int rowAddTimeRemainingMs) const;
    void drawRow(const Board::Row& row, int fallingCol, const std::vector<bool>* pieceBits) const;

    // Maps operator enum to display string.
    static std::string opLabel(Board::Operator op);

    // ANSI escape helpers
    static void clearScreen();
    static void moveCursorHome();
    
    public:
    // Full-screen redraw.
    // upcomingPiece / heldPiece may be nullptr if not applicable.
    void draw(const Board& board,
              const FallingPiece* fallingPiece,
              const Piece* upcomingPiece,
              const Piece* heldPiece,
              int score,
              int level,
              int rowAddTimeRemainingMs = 0) const;
};

#endif