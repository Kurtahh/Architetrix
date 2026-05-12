#ifndef PIECELOADER_H
#define PIECELOADER_H

#include <vector>
#include <fstream>
#include <random>
#include "piece.h"

class PieceLoader {
    std::vector<Piece> easyPieces; //vector for each difficulty of pieces
    std::vector<Piece> mediumPieces;
    std::vector<Piece> hardPieces;

    void loadFromFile(std::ifstream& ifstr, std::vector<Piece>& pieces); //fills the vector from input file
    void loadPieces(); //calls loadFromFile() for each difficulty vector

    public:
    PieceLoader(); //calls loadPieces()
    Piece getRandomPiece(int difficulty) const; //getter for a random piece based on difficulty parameter
    std::vector<Piece> getEasy() const; //getters for each field
    std::vector<Piece> getMedium() const;
    std::vector<Piece> getHard() const;
};

#endif