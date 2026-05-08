#include "pieceLoader.h"
using namespace std;

const string EASY_FILE = "data/easy.txt";
const string MEDIUM_FILE = "data/medium.txt";
const string HARD_FILE = "data/hard.txt";

void PieceLoader::loadFromFile(ifstream& ifstr, vector<Piece>& pieces)
{
    string line;
    vector<vector<bool>> tempRows;
    vector<bool> tempRow;
    while(getline(ifstr, line)){
        if(line.back() != ','){
            for(char c : line){
                if(c == '1') tempRow.push_back(1);
                else tempRow.push_back(0);
            }
            tempRows.push_back(tempRow);
        }
        else {
            for(char c : line){
                if(c == '1') tempRow.push_back(1);
                else if(c == '0') tempRow.push_back(0);
            }
            tempRows.push_back(tempRow);
            pieces.push_back(Piece(tempRows));
            tempRows.clear();
        }
        tempRow.clear();
    }
    if(!tempRows.empty()) pieces.push_back(Piece(tempRows));
}
    
void PieceLoader::loadPieces()
{
    ifstream easyStream(EASY_FILE);
    loadFromFile(easyStream, easyPieces);

    ifstream mediumStream(MEDIUM_FILE);
    loadFromFile(mediumStream, mediumPieces);

    ifstream hardStream(HARD_FILE);
    loadFromFile(hardStream, hardPieces);
}

PieceLoader::PieceLoader()
{
    loadPieces();
}

vector<Piece> PieceLoader::getEasy()
{
    return easyPieces;
}
vector<Piece> PieceLoader::getMedium()
{
    return mediumPieces;
}
vector<Piece> PieceLoader::getHard()
{
    return hardPieces;
}