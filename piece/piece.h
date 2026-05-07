#ifndef PIECE_H
#define PIECE_H

#include <vector>

class Piece{
    std::vector<std::vector<bool>> bits;
    int width;
    int height;

    public:
    std::vector<std::vector<bool>> getBits();
    int getWidth();
    int getHeight();
    void setBits(std::vector<std::vector<bool>> newBits);
};

#endif