#ifndef PIECELOADER_H
#define PIECELOADER_H

#include <vector>
#include <fstream>
#include <random>
#include "piece.h"

class PieceLoader {
    std::vector<Piece> easyPieces;
    std::vector<Piece> mediumPieces;
    std::vector<Piece> hardPieces;

    void loadFromFile(std::ifstream& ifstr, std::vector<Piece>& pieces);
    void loadPieces();

    public:
    PieceLoader();
    Piece getRandomPiece(int difficulty) const;
    std::vector<Piece> getEasy();
    std::vector<Piece> getMedium();
    std::vector<Piece> getHard();
};

#endif