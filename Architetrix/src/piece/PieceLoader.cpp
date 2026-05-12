#include "PieceLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

Piece PieceLoader::parsePiece(const std::vector<std::string>& rows) {
    std::vector<std::vector<bool>> bits;
    for (const auto& row : rows) {
        std::vector<bool> line;
        for (char c : row) {
            if (c == '1') line.push_back(true);
            else if (c == '0') line.push_back(false);
        }
        if (!line.empty()) bits.push_back(line);
    }
    return Piece(bits);
}

void PieceLoader::loadPieces() {
    loadFromFile("src/data/easy.txt", easy_);
    loadFromFile("src/data/medium.txt", medium_);
    loadFromFile("src/data/hard.txt", hard_);
    
    //uses built in defaults if files are inaccessible
    if (easy_.empty() && medium_.empty() && hard_.empty()) {
        std::cerr << "[PieceLoader] No piece data files found — using built-in defaults.\n";
        loadDefaults();
    }
}

void PieceLoader::loadFromFile(const std::string& filePath, std::vector<Piece>& pieces) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        return;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        //skips comments and empty lines
        if (line.empty() || line[0] == '#') {
            continue;
        }
        
        if (line.back() != ',') {
            continue;  //skips lines that don't end with comma
        }
        
        //parsing bits
        line.pop_back();
        
        std::vector<bool> row;
        for (char c : line) {
            if (c == '1') 
                row.push_back(true);
            else if (c == '0') 
                row.push_back(false);
        }
        
        //creating the piece
        if (!row.empty()) {
            std::vector<std::vector<bool>> grid;
            grid.push_back(row);
            pieces.push_back(Piece(grid));
        }
    }
}

const std::vector<Piece>& PieceLoader::getEasy() const { 
    return easy_;
}

const std::vector<Piece>& PieceLoader::getMedium() const { 
    return medium_; 
}

const std::vector<Piece>& PieceLoader::getHard() const { 
    return hard_; 
}

Piece PieceLoader::getRandomPiece(int difficulty) const {
    static std::mt19937 rng(std::random_device{}());
    
    const std::vector<Piece>* pool = nullptr;
    
    if (difficulty == 1) {
        pool = &easy_;
    } else if (difficulty == 2) {
        pool = &medium_;
    } else if (difficulty == 3) {
        pool = &hard_;
    } else {
        pool = &easy_;  //default to easy
    }
    
    if (pool->empty()) {
        return Piece();  //return empty piece if pool is empty
    }
    
    std::uniform_int_distribution<int> dist(0, pool->size() - 1);
    return (*pool)[dist(rng)];
}

///Helper: builds a 1-row Piece from a string of 1's and 0's
static Piece makeRow(const char* s) {
    std::vector<bool> row;
    for (const char* c = s; *c; ++c)
        row.push_back(*c == '1');
    std::vector<std::vector<bool>> grid;
    grid.push_back(row);
    return Piece(grid);
}

void PieceLoader::loadDefaults() {
    easy_.push_back(makeRow("1111"));
    easy_.push_back(makeRow("1010"));
    easy_.push_back(makeRow("0110"));
    easy_.push_back(makeRow("1100"));
    easy_.push_back(makeRow("1001"));

    medium_.push_back(makeRow("11011"));
    medium_.push_back(makeRow("01110"));
    medium_.push_back(makeRow("10101"));
    medium_.push_back(makeRow("11101"));

    hard_.push_back(makeRow("111111"));
    hard_.push_back(makeRow("101101"));
    hard_.push_back(makeRow("0011100"));
}