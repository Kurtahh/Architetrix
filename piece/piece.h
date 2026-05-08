#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <string>
#include <sstream>

class Piece{
    std::vector<std::vector<bool>> rows;
    int width;

    public:
    Piece(std::vector<std::vector<bool>>);
    std::vector<std::vector<bool>> getRows();
    std::vector<std::vector<bool>>& Piece::getRowsRef();
    int getWidth();
    int getHeight();
    std::string toString();
    std::string toDebugString();
};

#endif