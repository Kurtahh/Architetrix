#include <iostream>
#include <termios.h>
#include <unistd.h>
#include "game/GameLoop.h"

struct Terminal {
    termios original;
    Terminal() {
        tcgetattr(STDIN_FILENO, &original);
        termios raw = original;
        raw.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &raw);
    }
    ~Terminal() {
        tcsetattr(STDIN_FILENO, TCSANOW, &original);
    }
};

int main() {
    Terminal term;

    GameLoop game;
    game.init();
    game.run();

    return 0;
}