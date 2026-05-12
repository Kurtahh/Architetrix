#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <string>
#include <sstream>

class Piece{
    std::vector<std::vector<bool>> rows; //the piece itself
    int width; //the widest row's width in the piece

    public:
    Piece(std::vector<std::vector<bool>>); //writes width field based on parameter
    std::vector<std::vector<bool>> getRows() const;  //getter for raw piece data
    std::vector<std::vector<bool>>& getRowsRef(); //getter for reference to data. Used to invert bits without copying the vector
    int getWidth() const; //getter for width field
    int getHeight() const; //getter for rows.size() (which is the height of the piece)
    std::string toString() const; //returns the piece as a string (with newlines already where they need to be)
    std::string toDebugString() const; //returns width and height with a space between them
};

#endif