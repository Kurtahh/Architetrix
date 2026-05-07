#include "piece.h"
using namespace std;

vector<vector<bool>> Piece::getBits() {
    return bits;
}
int Piece::getWidth() {
    return width;
}
int Piece::getHeight() {
    return bits.size();
}

void Piece::setBits(vector<vector<bool>> newBits) {
    bits = newBits;
    //ENDED HERE, HAVE TO REDETERMINE THE WIDTH FIELD FOR NEW BITS
    //for()
}

