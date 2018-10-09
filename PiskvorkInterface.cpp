//
// Created by nils on 08/10/2018.
//

#include <cstring>
#include "PiskvorkInterface.hpp"

PiskvorkInterface::PiskvorkInterface() = default;

PiskvorkInterface::~PiskvorkInterface() = default;


void PiskvorkInterface::waitCommand() {
    // optimisation durant le temps de l'adversaire
    std::string     input;
    std::getline(std::cin, input);
    char    *token = std::strtok(const_cast<char *>(input.c_str()), " ,");

    command.clear();
    while (token != NULL) {
        command.emplace_back(token);
        token = std::strtok(NULL, " ,");
    }
}

void PiskvorkInterface::mainLoop() {
    while (run) {
        waitCommand();
        std::string ins = command.front();

        ((this)->*callInstruction[ins])();
    }
}

void PiskvorkInterface::start() {
    // set board size
    boardSize = std::stoi(command[1]);
}

void PiskvorkInterface::turn() {
    // rajouter gestion erreur ici
    addMove(std::stoi(command[1]), std::stoi(command[2]));
    //std::cout << curPlate << std::endl;
    playMove();
}

void PiskvorkInterface::begin() {
    playMove();
}

void PiskvorkInterface::board() {
    unknown();
}

void PiskvorkInterface::info() {
    unknown();
}

void PiskvorkInterface::end() {
    run = false;
}

void PiskvorkInterface::about() {
    std::cout << R"(name="GradeAgo", version="1.1", author="Nils", epitech="Marseille")" << std::endl;
}

void PiskvorkInterface::unknown() {
    std::cout << "UNKNOWN - INSTRUCTION NOT IMPLEMENTED" << std::endl;
}

void PiskvorkInterface::error() {
    std::cout << "ERROR - ERROR WHILE PROCESSING" << std::endl;
}

void PiskvorkInterface::debug(std::string &s) {
    std::cout << "DEBUG - " << s << std::endl;
}

/* opponent move */
void PiskvorkInterface::addMove(int y, int x) {
    curPlate[POS(y, x)] = BLACK;
}

void PiskvorkInterface::playMove() {
    std::cout << rand() % 19 << "," << rand() % 19 << std::endl;
}
