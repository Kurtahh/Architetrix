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
    // Level thresholds: unlock operators progressively
    // Level 1: AND, OR (basics)
    // Level 2-4: NAND, NOR (still manageable)
    // Level 5+: XOR, XNOR (harder)
    
    int maxOp = 1;  // AND, OR only
    
    if (level >= 2) 
        maxOp = 3;  // + NAND, NOR
    if (level >= 5) 
        maxOp = 4;  // + XOR
    if (level >= 6) 
        maxOp = 5;  // + XNOR

    switch (rand() % (maxOp + 1)) {
        case 0: 
            return Board::Operator::AND;
        case 1: 
            return Board::Operator::OR;
        case 2: 
            return Board::Operator::NAND;
        case 3: 
            return Board::Operator::NOR;
        case 4: 
            return Board::Operator::XOR;
        case 5: 
            return Board::Operator::XNOR;
        default: 
            return Board::Operator::OR;
    }
}