//
// Created by nils on 08/10/2018.
//

#ifndef IA_BOARD_H
#define IA_BOARD_H

#include <string>
#include <vector>

#define EMPTY 0
/* black is the enemy */
#define BLACK 1
/* board considere i'm always white */
#define WHITE 2
inline char PIECE_ASCII(char x) { return (x == 0 ? '.' : x == 1 ? 'O' : 'X'); }

#define WIDTH 19
#define HEIGHT 19
#define FULLSIZE (WIDTH * HEIGHT)
#define COMPRESSED_SIZE (FULLSIZE / 4 + 1)
#define POS(y, x) (y * HEIGHT + x)

class Board {
public:

    Board();
    Board(const Board &) = default;
    ~Board();

    void    emptyBoard();

    void    compress();
    void    decompress();

    // first move
    void    initPlayingZone(short);

    void    playOnCompressed(short, char);
    void    play(short, char);

    std::vector<short>    getPossiblesMoves();
    std::vector<short>    epurePossiblesMoves();

    char  &operator[](int);
    friend std::ostream &operator<<(std::ostream &, const Board &);

    short   last_play = -1;
    std::string   plate;
    // y, x, yl, xl
    short   playingZone[4] = {-1, -1, 1, 1};

private:
    bool    compressed = false;
};

#endif //IA_BOARD_H