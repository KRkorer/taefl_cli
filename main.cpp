#include <iostream>
#include <cmath>
#include "taefl.h"

int main (int argc, char const *argv[]) {
    Taefl taefl;
    bool stop = false;
    char answer = 'y';
    while (!stop) {
        taefl.game();
        std::cout << "Would you like to play once more? (y/n)" << '\n';
        std::cin >> answer;
        if ((answer == 'n') or (answer == 'N')){
            stop = true;
        }
    }

    return 0;
}
