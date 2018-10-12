//
// Created by nils on 12/10/18.
//

#ifndef IA_MINMAXALPHABETA_HPP
#define IA_MINMAXALPHABETA_HPP

#include <cfloat>

#include "Board.hpp"
#include "TreeNode.tpp"
#include "Evaluator.hpp"

typedef char MINMAX;
#define MIN 0
#define MAX 1

class   Node {
    short   prevMove;
    char    playerWhoPlayed;
};

// je joue toujours les blanc et l'adversaire toujours les noirs
class MinMaxAlphaBeta {
public:
    MinMaxAlphaBeta() = default;

    // we propagate all the moves on the tree
    void    deepSimulation(TreeNode<Node> *, Board);
    // we evaluate nodes and process backpropagation
    void    retroPropagation(TreeNode<Node> *, MINMAX);

    void    propagation();
    short   getBestMove();

    void    addMove(int, int);
    void    play();


    bool    timerEnd();
private:
    Board   curPlate;

    TreeNode<Board>   tree;
    Evaluator   evaluator;
    short   curDeep;

    bool    firstMove = true;
    clock_t timer;
};



#endif //IA_MINMAXALPHABETA_HPP
