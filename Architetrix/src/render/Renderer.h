#ifndef RENDERER_H_477211
#define RENDERER_H_477211

#include "../board/Board.h"
#include <string>
#include <vector>

class FallingPiece;
class Piece;  // for held/upcoming

// Renderer owns no state — it reads const refs and writes to stdout each tick.
class Renderer {
    void drawBoard(const Board& board, const FallingPiece* piece) const;
    void drawSidebar(const Piece* upcoming, const Piece* held, int score, int level, int rowAddTimeRemainingMs, int personalRecord) const;    void drawRow(const Board::Row& row, int fallingCol, const std::vector<bool>* pieceBits) const;

    // Maps operator enum to display string with colors.
    static std::string opLabel(Board::Operator op);
    
    // Color helpers for operators
    static std::string getOpColor(Board::Operator op);
    static const std::string RESET;

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
          int rowAddTimeRemainingMs = 0,
          int personalRecord = 0) const;
    
    // Flash animation for cleared rows (animated with cool symbols)
    // Only animates the specified row indices
    void flashClearRows(const std::vector<Board::Row>& rowsBeforeClear,
                       const std::vector<int>& clearedRowIndices,
                       const Piece* upcomingPiece,
                       const Piece* heldPiece,
                       int score,
                       int level,
                       int personalRecord) const;
    
    // Flashy game over screen
    void displayGameOver(int score, int level, int personalRecord, bool newRecord) const;
};

#endif