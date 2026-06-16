#include "EliminationChecker.h"
#include <vector>
#include <algorithm>

EliminationChecker::ClearResult EliminationChecker::checkAndClear(Board& board) const {
    ClearResult result;

    // Check for full rows AND empty rows
    std::vector<int> rowsToRemove;
    for (int r = 0; r < board.getHeight(); ++r) {
        if (isRowFull(board.getRows()[r]) || isRowEmpty(board.getRows()[r])) 
            rowsToRemove.push_back(r);
    }

    // Store cleared row indices for animation
    result.clearedRowIndices = rowsToRemove;

    // Remove rows (sort descending to preserve indices)
    std::sort(rowsToRemove.rbegin(), rowsToRemove.rend());
    for (int r : rowsToRemove)
        board.removeRow(r);

    result.rowsCleared = static_cast<int>(rowsToRemove.size());
    result.colsCleared = 0;
    result.perfectClear = false;
    result.scoreGained = computeScore(result);

    return result;
}

bool EliminationChecker::isRowFull(const Board::Row& row) const {
    for (bool b : row.bits) 
        if (!b) 
            return false;
    
    return !row.bits.empty();
}

bool EliminationChecker::isRowEmpty(const Board::Row& row) const {
    for (bool b : row.bits)
        if (b) 
            return false;

    return true;
}

int EliminationChecker::computeScore(const ClearResult& result) const {
    // Score based on rows cleared only
    if (result.rowsCleared > 0)          
        return result.rowsCleared * 100;

    return 0;
}