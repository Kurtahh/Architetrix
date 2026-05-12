#include "piece.h"
using namespace std;

Piece::Piece(vector<vector<bool>> setRows) {
    rows = setRows;
    int maxWidth = rows.at(0).size();
    for(auto line : rows){
        if(maxWidth < line.size()) maxWidth = line.size();
    }
    width = maxWidth;
}

vector<vector<bool>> Piece::getRows() const{
    return rows;
}
vector<vector<bool>>& Piece::getRowsRef() {
    return rows;
}
int Piece::getWidth() const{
    return width;
}
int Piece::getHeight() const{
    return rows.size();
}

string Piece::toString() const{
    stringstream ss;
    for(auto& row : rows){
        for(bool bit : row){
            ss << bit;
        }
        ss << '\n';
    }
    return ss.str();
}
string Piece::toDebugString() const{
    stringstream ss;
    //width height
    ss << width << " " << rows.size();
    return ss.str();
}

