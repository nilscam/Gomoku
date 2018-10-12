//
// Created by nils on 11/10/18.
//

#ifndef IA_MINMAX_HPP
#define IA_MINMAX_HPP

#include <cfloat>

#include "Board.hpp"
#include "TreeNode.tpp"
#include "Evaluator.hpp"

typedef char MINMAX;
#define MIN 0
#define MAX 1

// je joue toujours les blanc et l'adversaire toujours les noirs
class MinMax {
public:
    MinMax() = default;

    // we propagate all the moves on the tree
    void    deepSimulation(TreeNode<Board> *);
    // we evaluate nodes and process backpropagation
    void    retroPropagation(TreeNode<Board> *, MINMAX);

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


#endif //IA_MINMAX_HPP
