//
// Created by nils on 08/10/2018.
//

#include <iostream>
#include "Board.hpp"

Board::Board() : plate(FULLSIZE, 0) {}

Board::~Board() = default;

void Board::emptyBoard() {
    for (int i = 0; i < FULLSIZE; i++)
        plate[i] = 0;
}

void Board::compress() {
    if (!compressed) {
        std::string old(plate);

        plate.resize(COMPRESSED_SIZE);
        plate.reserve(COMPRESSED_SIZE);
        for (int i = 0; i < COMPRESSED_SIZE - 1; i++)
            plate[i] = ((old[i * 4] << 6) + (old[i * 4 + 1] << 4) + (old[i * 4 + 2] << 2) + (old[i * 4 + 3]));
        plate[COMPRESSED_SIZE - 1] = old[FULLSIZE - 1] << 6;
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

void Board::play(short pos, char player) {
    auto y = static_cast<short>(pos / HEIGHT);
    auto x = static_cast<short>(pos % WIDTH);

    // y
    if (y - 2 < playingZone[0]) {
        playingZone[2] += static_cast<short>(playingZone[0] - (y - 2));
        playingZone[0] = static_cast<short>(y - 2 < playingZone[0] ? (y - 2 < 0 ? 0 : y - 2) : playingZone[0]);
    } else if (y + 2 > playingZone[0] + playingZone[2]) {
        playingZone[2] += ((y + 2) - (playingZone[0] + playingZone[2]));
    }

    // x
    if (x - 2 < playingZone[1]) {
        playingZone[3] += static_cast<short>(playingZone[1] - (x - 2));
        playingZone[1] = static_cast<short>(x - 2 < playingZone[1] ? (x - 2 < 0 ? 0 : x - 2) : playingZone[1]);
    } else if (x + 2 > playingZone[1] + playingZone[3]) {
        playingZone[3] += ((x + 2) - (playingZone[1] + playingZone[3]));
    }

    if (compressed) {
        playOnCompressed(pos, player);
    } else {
        plate[pos] = player;
    }
}

std::vector<short> Board::getPossiblesMoves() {
    decompress();
    std::vector<short>     moves;

    moves.reserve(361);
    for (int i = 0; i < FULLSIZE; i++)
        if (plate[i] == EMPTY)
            moves.push_back(i);
    moves.reserve(moves.size());
    compress();
    return moves;
}

std::vector<short> Board::epurePossiblesMoves() {
    return std::vector<short>();
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
        os << "Playing zone : [" << board.playingZone[0] << "," << board.playingZone[1] << "] [" << board.playingZone[2] << "," << board.playingZone[3] << "]" << std::endl;
        return os << std::endl;
    } else {
        Board   copy(board);

        copy.decompress();
        return os << copy;
    }
}

void Board::playOnCompressed(short pos, char player) {
    unsigned char filter = ((unsigned char)(16191 >> ((pos % 4)) * 2));
    plate[pos / 4] = (player << ((3 - (pos % 4)) * 2)) | (plate[pos / 4] & filter);
}

void Board::initPlayingZone(short pos) {
    auto y = static_cast<short>(pos / HEIGHT);
    auto x = static_cast<short>(pos % WIDTH);

    playingZone[0] = static_cast<short>(y - 2 < 0 ? 0 : y - 2);
    playingZone[1] = static_cast<short>(x - 2 < 0 ? 0 : x - 2);

    playingZone[2] -= y > 16 ? 21 - y : 0;
    playingZone[3] -= x > 16 ? 21 - x : 0;
}

