#include "EliminationChecker.h"
#include <vector>
#include <algorithm>

EliminationChecker::ClearResult EliminationChecker::checkAndClear(Board& board) const {
    ClearResult result;

    std::vector<int> fullRows;
    for (int r = 0; r < board.getHeight(); ++r)
        if (isRowFull(board.getRows()[r])) 
            fullRows.push_back(r);

    std::vector<int> fullCols;
    for (int c = 0; c < Board::WIDTH; ++c)
        if (isColumnFull(board, c)) 
            fullCols.push_back(c);

    std::vector<int> emptyRows;
    for (int r = 0; r < board.getHeight(); ++r)
        if (isRowEmpty(board.getRows()[r])) 
            emptyRows.push_back(r);

    result.perfectClear = (!fullRows.empty() && !fullCols.empty());

    // Remove columns first (indices don't shift)
    // Remove in reverse order to preserve indices
    for (int i = static_cast<int>(fullCols.size()) - 1; i >= 0; --i)
        board.removeColumn(fullCols[i]);

    result.colsCleared = static_cast<int>(fullCols.size());

    // Remove full rows + empty rows (collect all, deduplicate, sort descending)
    std::vector<int> rowsToRemove = fullRows;

    for (int r : emptyRows) {
        if (std::find(rowsToRemove.begin(), rowsToRemove.end(), r) == rowsToRemove.end())
            rowsToRemove.push_back(r);
    }

    std::sort(rowsToRemove.rbegin(), rowsToRemove.rend());

    for (int r : rowsToRemove)
        board.removeRow(r);

    result.rowsCleared = static_cast<int>(rowsToRemove.size());

    result.scoreGained = computeScore(result);

    return result;
}

bool EliminationChecker::isRowFull(const Board::Row& row) const {
    for (bool b : row.bits) 
        if (!b) 
            return false;
    
    return !row.bits.empty();
}

bool EliminationChecker::isColumnFull(const Board& board, int col) const {
    if (board.getHeight() == 0) 
        return false;

    for (const auto& row : board.getRows()) {
        if (col >= static_cast<int>(row.bits.size()) || !row.bits[col])
            return false;
    }
    
    return true;
}

bool EliminationChecker::isRowEmpty(const Board::Row& row) const {
    for (bool b : row.bits)
        if (b) 
            return false;

    return true;
}

int EliminationChecker::computeScore(const ClearResult& result) const {
    if (result.perfectClear)
        return 500 + result.rowsCleared * 100 + result.colsCleared * 100;

    if (result.colsCleared > 0) 
        return result.colsCleared * 150;
        
    if (result.rowsCleared > 0)          
        return result.rowsCleared * 100;

    return 0;
}