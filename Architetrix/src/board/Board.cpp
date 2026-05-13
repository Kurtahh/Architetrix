#include "Board.h"
#include <stdexcept>

bool Board::addRowAtBottom(const Row& row) {
    if (isOverflowed()) 
        return false;
    rows_.push_back(row);

    return true;
}

const std::vector<Board::Row>& Board::getRows() const { 
    return rows_; 
}
std::vector<Board::Row>& Board::getRows() { 
    return rows_; 
}

int Board::getHeight() const { 
    return static_cast<int>(rows_.size()); 
}

int Board::getEmptyRows() const { 
    return VISIBLE_HEIGHT - getHeight();
}

void Board::setBoard(const std::vector<Row>& newRows) { 
    rows_ = newRows; 
}

void Board::removeRow(int index) {
    if (index < 0 || index >= getHeight())
        throw std::out_of_range("Board::removeRow: index out of range");
    rows_.erase(rows_.begin() + index);
}

void Board::removeColumn(int col) {
    if (col < 0 || col >= WIDTH)
        throw std::out_of_range("Board::removeColumn: col out of range");
    for (auto& row : rows_) {
        // Ensure row is at full width, then set the column to 0
        if (row.bits.size() < static_cast<size_t>(WIDTH)) {
            row.bits.resize(WIDTH, false);
        }
        if (col < static_cast<int>(row.bits.size())) {
            row.bits[col] = false;
        }
    }
}

bool Board::isOverflowed() const {
    return getHeight() >= VISIBLE_HEIGHT;
}