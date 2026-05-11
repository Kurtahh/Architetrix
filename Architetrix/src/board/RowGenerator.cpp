#include "RowGenerator.h"
#include <cstdlib>

Board::Row RowGenerator::generate(int level) const {
    Board::Row row;
    row.bits.resize(Board::WIDTH);
    for (int i = 0; i < Board::WIDTH; ++i)
        row.bits[i] = (rand() % 2 == 1);
    row.op = pickOperator(level);

    return row;
}

Board::Operator RowGenerator::pickOperator(int level) const {
    // Level thresholds: AND/OR always, XOR from level 3, NAND/NOR from level 5
    int maxOp = 1;  // AND, OR only
    
    if (level >= 3) 
        maxOp = 2;  // + XOR
    if (level >= 5) 
        maxOp = 4;  // + NAND, NOR

    switch (rand() % (maxOp + 1)) {
        case 0: 
            return Board::Operator::AND;
        case 1: 
            return Board::Operator::OR;
        case 2: 
            return Board::Operator::XOR;
        case 3: 
            return Board::Operator::NAND;
        case 4: 
            return Board::Operator::NOR;
        default: 
            return Board::Operator::OR;
    }
}