#include "pieceController.h"
using namespace std;

PieceController::PieceController(const PieceLoader& loader) :
    difficulty(1),
    falling(loader.getRandomPiece(difficulty)),
    prevFalling(falling), //dummy value until first piece falls
    held(),
    upcoming(),
    loader(loader),
    hasHeld(false) {
        for(int i = 0; i < 3; i++){
            upcoming.push_back(loader.getRandomPiece(difficulty));
        }
    }

void PieceController::dropFalling(const Board& board)
{
    //falling.setY(board.getTopOccupiedRow(x));
    prevFalling = falling;
    falling = FallingPiece(upcoming.front());
    upcoming.pop_front();
    upcoming.push_back(loader.getRandomPiece(difficulty));
    hasHeld = false;
}

void PieceController::holdFalling()
{
    if(hasHeld) return;
    if(held.has_value()){
        auto temp = held.value();
        held = falling.getPiece();
        falling.setPiece(temp);
    }
    else {
        held = falling.getPiece();
        falling = FallingPiece(upcoming.front());
        upcoming.pop_front();
        upcoming.push_back(loader.getRandomPiece(difficulty));
    }
    hasHeld = true;
}

FallingPiece PieceController::getFalling() {
    return falling;
}

optional<Piece> PieceController::getHeld() {
    return held;
}

deque<Piece> PieceController::getUpcoming() {
    return upcoming;
}

int PieceController::getDifficulty() {
    return difficulty;
}

void PieceController::setDifficulty(int newDiff) {
    difficulty = newDiff;
}

void PieceController::resolveInput(Action action, const Board& board)
{
    switch(action){
        //WILL NEED TO ADD BOUNDARY CHECKING ONCE BOARD EXISTS
        case Action::MOVE_LEFT:
            falling.setX(falling.getX() - 1);
        break;
        case Action::MOVE_RIGHT:
            falling.setX(falling.getX() + 1);
        break;
        case Action::DROP:
            dropFalling(board);    
        break;
        case Action::HOLD:
            holdFalling();
        break;
        case Action::INVERT:
            falling.invertBits();
        break;
    }
}