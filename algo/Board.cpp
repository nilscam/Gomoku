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

    if (playingZone[0] == -1) {
        // Must be init
        initPlayingZone(pos);
    } else {
        auto y = static_cast<short>(pos / HEIGHT);
        auto x = static_cast<short>(pos % WIDTH);

        if (y < playingZone[0]) {
            playingZone[2] += playingZone[0] - y;
            playingZone[0] = y;
        } else if (playingZone[0] + playingZone[2] < (y + 1)) {
            playingZone[2] += (y + 1) - (playingZone[0] + playingZone[2]);
        }

        if (x < playingZone[1]) {
            playingZone[3] += playingZone[1] - x;
            playingZone[1] = x;
        } else if (playingZone[1] + playingZone[3] < (x + 1)) {
            playingZone[3] += (x + 1) - (playingZone[1] + playingZone[3]);
        }
    }

    if (compressed) {
        playOnCompressed(pos, player);
    } else {
        plate[pos] = player;
    }
    last_play = pos;
}

std::vector<short> Board::getPossiblesMoves() {
    decompress();
    std::vector<short>     moves;

    moves.reserve(361);
    for (short y = playingZone[0] - 2; y < playingZone[0] + playingZone[2] + 2; y++)
        for (short x = playingZone[1] - 2; x < playingZone[1] + playingZone[3] + 2; x++) {
            if (y >= 0 && x >= 0 && y < HEIGHT && x < WIDTH && plate[POS(y, x)] == EMPTY)
                moves.push_back(POS(y, x));
        }

            /*
    for (int i = 0; i < FULLSIZE; i++)
        if (plate[i] == EMPTY)
            moves.push_back(i);
             */
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

    playingZone[0] = y;
    playingZone[1] = x;

    playingZone[2] = 1;
    playingZone[3] = 1;
}

