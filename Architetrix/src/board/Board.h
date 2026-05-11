#ifndef BOARD_H_727233
#define BOARD_H_727233

#include <vector>
#include <cstdint>

class Board {
public:
    enum class Operator { AND, OR, XOR, NAND, NOR };

    struct Row {
        std::vector<bool> bits;
        Operator op;
    };

    static constexpr int WIDTH = 16;
    static constexpr int VISIBLE_HEIGHT = 20;

    Board() = default;

    /// Add a new row at the bottom of the stack.
    /// Returns false if the stack has grown to fill the entire visible area (game over).
    bool addRowAtBottom(const Row& row);

    /// Direct access for the engine / renderer.
    const std::vector<Row>& getRows() const;
    std::vector<Row>& getRows();

    /// Number of filled rows currently in the stack.
    int getHeight() const;

    /// Number of empty lines above the stack (VISIBLE_HEIGHT - getHeight()).
    int getEmptyRows() const;

    /// Replace the entire stack (e.g. after a clear).
    void setBoard(const std::vector<Row>& newRows);

    /// Remove a single row by index (within the filled stack).
    void removeRow(int index);

    /// Remove a single column across all rows.
    void removeColumn(int col);

    /// Returns true if the stack has grown to fill the entire visible area.
    bool isOverflowed() const;

private:
    std::vector<Row> rows_;
};

#endif