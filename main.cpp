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

//05:38 - 6:45
//08:20 - 10:17