//
// Created by nils on 08/10/2018.
//

#include <iostream>
#include "Board.hpp"

Board::Board() : plate(FULLSIZE, 0) {
}

Board::~Board() = default;

void Board::emptyBoard() {
    for (int i = 0; i < FULLSIZE; i++)
        plate[i] = 0;
}


void Board::compress() {
    if (!compressed) {
        std::string old(plate);

        plate.resize(COMPRESSED_SIZE);
        for (int i = 0; i < COMPRESSED_SIZE; i++)
            plate[i] = ((old[i * 4] << 6) + (old[i * 4 + 1] << 4) + (old[i * 4 + 2] << 2) + (old[i * 4 + 3]));
        compressed = true;
    }
}

void Board::decompress() {
    if (compressed) {
        std::string old(plate);

        plate.resize(FULLSIZE);
        for (int i = 0; i < FULLSIZE; i++)
            plate[i] = static_cast<char>(old[i / 4] >> ((3 - (i % 4)) * 2) & 3);
        compressed = false;
    }
}


char &Board::operator[](int pos) {
    return plate[pos];
}

std::ostream &operator<<(std::ostream &os, const Board &board) {
    if (!board.compressed) {
        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                os << PIECE_ASCII(board.plate[POS(y, x)]);
            }
            os << std::endl;
        }
        return os << std::endl;
    } else {
        Board   copy(board);

        copy.decompress();
        return os << copy;
    }
}
