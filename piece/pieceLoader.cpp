#include <fstream>
#include <vector>
#include <iostream>
#include "piece.h"
using namespace std;

const string EASY_FILE = "data/easy.txt";
const string MEDIUM_FILE = "data/medium.txt";
const string HARD_FILE = "data/hard.txt";

class PieceLoader {
    vector<Piece> easyPieces;
    vector<Piece> mediumPieces;
    vector<Piece> hardPieces;

    void loadFromFile(ifstream& ifstr, vector<Piece>& pieces)
    {
        //ENDED HERE, HAVE TO REFACTOR THE CODE TO USE PIECE'S METHODS FOR SETTING THE BITS AND USE SETBITS(...)
        // Piece piece;
        // string line;
        // int row = 0;
        // vector<bool> temp;
        // while(getline(ifstr, line)){
        //     if(line.back() != ','){
        //         for(char c : line){
        //             if(c == '1') temp.push_back(1);
        //             else temp.push_back(0);
        //         }
        //         piece.bits.push_back(temp);
        //     }
        //     else {
        //         for(char c : line){
        //             if(c == '1') temp.push_back(1);
        //             else if(c == '0') temp.push_back(0);
        //         }
        //         piece.bits.push_back(temp);
        //         pieces.push_back(piece);
        //         piece.bits.clear();
        //     }
        //     temp.clear();
        // }
    }    
};

//16:16 - 17:55
//18:29 - 19:28