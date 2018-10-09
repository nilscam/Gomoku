//
// Created by nils on 08/10/2018.
//

#ifndef PBRAIN_GRADEAGO_PISKVORKINTERFACE_HPP
#define PBRAIN_GRADEAGO_PISKVORKINTERFACE_HPP

#include <iterator>
#include <iostream>
#include <sstream>
#include <map>
#include "algo/Board.hpp"

class PiskvorkInterface;
typedef void (PiskvorkInterface::*instruction)();

class PiskvorkInterface {
public:

    PiskvorkInterface();
    ~PiskvorkInterface();

    void    addMove(int, int);
    void    playMove();

    // instructions
    void    start();
    void    turn();
    void    begin();
    void    board();
    void    info();
    void    end();
    void    about();

    // responses
    static void    unknown();
    static void    error(std::string &);
    static void    debug(std::string &);

    void    waitCommand();

    void    mainLoop();

private:
    Board   curPlate;
    std::vector<std::string>    command;

    std::map<std::string, instruction>    callInstruction = {
            {"START", &PiskvorkInterface::start},
            {"BEGIN", &PiskvorkInterface::begin},
            {"TURN", &PiskvorkInterface::turn},
            {"BOARD", &PiskvorkInterface::board},
            {"INFO", &PiskvorkInterface::info},
            {"END", &PiskvorkInterface::end},
            {"ABOUT", &PiskvorkInterface::about}
    };

    bool    run = true;
    int     boardSize = 19;
};

#endif //PBRAIN_GRADEAGO_PISKVORKINTERFACE_HPP
