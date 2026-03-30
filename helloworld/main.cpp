#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <thread>
#include <chrono>

struct Terminal
{
    termios original;
    Terminal()
    {
        tcgetattr(STDIN_FILENO, &original);
        termios raw = original;
        raw.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &raw);
    }
    ~Terminal()
    {
        tcsetattr(STDIN_FILENO, TCSANOW, &original);
    }
};

int pos = 0;
int row = 0;
bool dropped = false;
bool running = true;

void render()
{
    std::cout << "\033[8A";
    for (int r = 0; r < 8; r++){
        std::cout << "\r\033[2K";
        if (r == row){
            for (int i = 0; i < pos; i++){
                std::cout << " ";
            }
            std::cout << "0101";
        }
        std::cout << "\n";
    }
    std::cout << std::flush;
}

void gravity()
{
    while (running){
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        if (dropped && row < 7){
            row++;
            render();
        }
    }
}

int main()
{
    Terminal term;

    for (int i = 0; i < 8; i++){
        std::cout << "\n";
    }
    render();

    std::thread gravThread(gravity);

    while (true){
        char c = getchar();
        if (c == 'q'){
            running = false;
            break;
        }
        if (!(dropped && row == 7)){
            if (c == 'a' && pos > 0)
                pos--;
            else if (c == 'd')
                pos++;
            else if (c == ' ' && !dropped)
                dropped = true;
        }
        render();
    }

    gravThread.join();
    std::cout << "\n";
    return 0;
}