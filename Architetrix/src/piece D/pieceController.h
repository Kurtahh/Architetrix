#ifndef PIECECONTROLLER_H
#define PIECECONTROLLER_H

#include <deque>
#include <optional>
#include "fallingPiece.h"
#include "pieceLoader.h"

class Board; //temp class for passing in methods of PieceController

enum class Action { //enum for each type of button press
    MOVE_LEFT,
    MOVE_RIGHT,
    DROP,
    HOLD,
    INVERT
};

class PieceController {
    FallingPiece falling;
    FallingPiece prevFalling; //allows for spawning new piece and bitwise operations to happen at once
    std::optional<Piece> held;
    std::deque<Piece> upcoming; //holds 3 pieces at a time
    const PieceLoader& loader; //to fetch pieces from
    int difficulty;
    bool hasHeld; //for making it so that u can only hold 1 piece per falling piece

    void dropFalling(const Board& board); //when user presses space to drop the piece
    void holdFalling(); //when user presses H to hold piece

    public:
    PieceController(const PieceLoader& loader); //initializes difficulty to 1, fills upcoming pieces deque w random easy pieces

    FallingPiece getFalling() const; //standard getters and setters
    FallingPiece getPrev() const;
    std::optional<Piece> getHeld() const;
    std::deque<Piece> getUpcoming() const;
    int getDifficulty() const;
    void setDifficulty(int newDiff);
    
    void resolveInput(Action action, const Board& board); //resolves each type of button press
};

#endif