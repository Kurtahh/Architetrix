#ifndef ROW_GENERATOR_H_332322
#define ROW_GENERATOR_H_332322

#include "../board/Board.h"

/// Generates new rows with random bit patterns and operators.
/// Operator complexity scales with level.
class RowGenerator {
public:
    /// level controls which operators can appear (higher = harder ops unlocked).
    Board::Row generate(int level) const;

private:
    Board::Operator pickOperator(int level) const;
};

#endif