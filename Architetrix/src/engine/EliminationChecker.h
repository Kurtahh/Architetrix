#ifndef ELIMINATION_CHECKER_H_096543
#define ELIMINATION_CHECKER_H_096543

#include "../board/Board.h"

/// Checks for and clears full rows, full columns, and cross (perfect) clears.
/// Returns the score for the current placement.
class EliminationChecker {
public:
    struct ClearResult {
        int rowsCleared = 0;
        int colsCleared = 0;
        bool perfectClear = false;  // simultaneous full row + full col
        int scoreGained = 0;
    };

    /// Scan the board, remove completed rows/cols, return scoring info.
    ClearResult checkAndClear(Board& board) const;

private:
    /// A row is "full" when every bit is true.
    bool isRowFull(const Board::Row& row) const;

    /// A column is "full" when every row has true at that index.
    bool isColumnFull(const Board& board, int col) const;

    /// A row is "empty" (basic clear) when every bit is false.
    bool isRowEmpty(const Board::Row& row) const;

    int computeScore(const ClearResult& result) const;
};

#endif