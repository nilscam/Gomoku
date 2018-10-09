#include <iostream>
#include <unistd.h>


#include "algo/Board.hpp"
#include "PiskvorkInterface.hpp"

int main() {
    PiskvorkInterface   program;

    program.mainLoop();
    return 0;
}