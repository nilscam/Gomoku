//
// Created by nils on 08/10/2018.
//

#include <iostream>
#include "Board.hpp"

Board::Board() : plate(WIDTH * HEIGHT) {
    emptyBoard();
}

Board::~Board() {

}

void Board::emptyBoard() {
    for (int i = 0; i < FULLSIZE; i++)
        plate[i] = 0;
}

char *Board::compressPosition() {
    return nullptr;
}

void Board::loadBoardFromHistory() {

}

void Board::loadBoardFromPosition() {

}

char &Board::operator[](int pos) {
    return plate[pos];
}

std::ostream &operator<<(std::ostream &os, const Board &board) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            os << PIECE_ASCII(board.plate[POS(y, x)]);
        }
        os << std::endl;
    }
    return os << std::endl;
}

/*
std::ostream &Board::operator<<(std::ostream &os) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            os << plate[POS(y, x)];
        }
        os << std::endl;
    }
    return os << std::endl;
}
 */
