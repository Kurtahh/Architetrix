#ifndef ELIMINATION_CHECKER_H_096543
#define ELIMINATION_CHECKER_H_096543

#include "../board/Board.h"
#include <vector>

/// Checks for and clears full rows and empty rows (no column clearing).
/// Returns the score for the current placement.
class EliminationChecker {
    public:
    struct ClearResult {
        int rowsCleared = 0;
        int colsCleared = 0;  // Always 0
        bool perfectClear = false;  // Always false
        int scoreGained = 0;
        std::vector<int> clearedRowIndices;  // Indices of rows that were cleared
    };

    /// Scan the board, remove completed rows, return scoring info.
    ClearResult checkAndClear(Board& board) const;

    private:
    /// A row is "full" when every bit is true.
    bool isRowFull(const Board::Row& row) const;

    /// A row is "empty" when every bit is false.
    bool isRowEmpty(const Board::Row& row) const;

    int computeScore(const ClearResult& result) const;
};

#endif