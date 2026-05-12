#ifndef PIECE_H_466778
#define PIECE_H_466778

#include <vector>
#include <string>
#include <sstream>

//piece is read only
//width/height describe the bounding box
class Piece {
    std::vector<std::vector<bool>> bits_;
    int width_ = 0;
    int height_ = 0;
    
    public:
    Piece() = default;
    Piece(std::vector<std::vector<bool>> bits);

    //const bits of piece, [height][width]
    const std::vector<std::vector<bool>>& getBits2D() const;

    //bits of piece by value
    std::vector<std::vector<bool>> getRows() const;

    //reference to bits of piece, used to invert bits without copying
    std::vector<std::vector<bool>>& getRowsRef();

    //flat data (row 0 col 0..n, row 1 col 0..n, ...) — used by Renderer sidebar
    std::vector<bool> getBits() const;

    int getWidth() const;
    int getHeight() const;

    //debug and display toString methods
    std::string toString() const;
    std::string toDebugString() const;
};

#endif