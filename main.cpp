#include <iostream>
#include "piece/piece.h"
#include "piece/pieceLoader.h"
using namespace std;

int main(){
    PieceLoader loader;
    for(auto& piece : loader.getEasy()){
        cout << piece.toDebugString() << endl << piece.toString() << endl;
    }
}

//9:10 - 10:12
//10:43 - 11:43
//12:03 - 