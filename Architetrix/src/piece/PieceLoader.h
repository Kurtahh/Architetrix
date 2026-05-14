#ifndef PIECE_LOADER_H_070098
#define PIECE_LOADER_H_070098

#include "Piece.h"
#include <vector>
#include <string>
#include <random>

//loads piece definitions from separate data files organized by difficulty

/// file format - (src/data/easy.txt, medium.txt, hard.txt):
///   0010,   <- single-row piece, ends with comma
///   101,
///   0100,
///   111,
///   ...
///
/// each line is a complete single-row piece (bits of 0s and 1s) ending with a comma
/// falls back to hardcoded defaults if data files are not found

class PieceLoader {
    std::vector<Piece> easy_;
    std::vector<Piece> medium_;
    std::vector<Piece> hard_;

    //loads single-row pieces from a file (comma-delimited format)
    void loadFromFile(const std::string& filePath, std::vector<Piece>& pieces);

    //falling back on hardcoded pieces when data files are not found
    void loadDefaults();

    //parses one piece block (list of bit-string rows) into a Piece
    static Piece parsePiece(const std::vector<std::string>& rows);
    
    public:
    //loads pieces from aforementioned files, falls back to built-in defaults if files are not found
    void loadPieces();

    const std::vector<Piece>& getEasy() const;
    const std::vector<Piece>& getMedium() const;
    const std::vector<Piece>& getHard() const;

    //gets a random piece based on difficulty level (1=easy, 2=medium, 3=hard)
    Piece getRandomPiece(int difficulty) const;
};

#endif