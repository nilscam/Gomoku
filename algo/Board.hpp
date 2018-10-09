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
#define POS(y, x) (y * HEIGHT + x)

class Board {
public:

    Board();
    ~Board();

    void    emptyBoard();

    static char    *compressPosition();
    void    loadBoardFromHistory();
    void    loadBoardFromPosition();

    char  &operator[](int);
    friend std::ostream &operator<<(std::ostream &, const Board &);

private:
    std::vector<char>   plate;
};

#endif //IA_BOARD_H
