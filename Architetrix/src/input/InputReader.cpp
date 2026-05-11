#include "InputReader.h"
#include <cstdio>

Action InputReader::readInput() const {
    char c = static_cast<char>(getchar());
    return mapChar(c);
}

Action InputReader::mapChar(char c) const {
    switch (c) {
        case 'a': 
            return Action::MOVE_LEFT;
        case 'd': 
            return Action::MOVE_RIGHT;
        case ' ': 
            return Action::HARD_DROP;
        case 'i': 
            return Action::INVERT;
        case 'h': 
            return Action::HOLD_SWAP;
        case 'q': 
            return Action::QUIT;
        default:  
            return Action::NONE;
    }
}