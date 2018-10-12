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
#define SWITCH_TARGET(t) (t == MIN ? MAX : MIN)
typedef char TURN;
#define SWITCH_PLAYER(p) (p == WHITE ? BLACK : WHITE)

// je joue toujours les blanc et l'adversaire toujours les noirs
class MinMax {
public:
    MinMax() = default;

    // retropropagation with alphaBeta algorithm
    float   alphaBeta(TreeNode<Board> *, float, float, MINMAX);
    // retropropagation without alphaBeta (evaluate every leaf)
    void    retroPropagation(TreeNode<Board> *, MINMAX);

    // we propagate all the moves on the tree
    void    deepSimulation(TreeNode<Board> *, TURN);

    void    propagation();
    short   getBestMove();

    void    addMove(int, int);
    void    play();


    bool    timerEnd();
private:
    Board   curPlate;

    TreeNode<Board>   *tree;
    Evaluator   evaluator;
    short   curDeep;

    bool    firstMove = true;
    clock_t timer;


    /* Statistiques */
    int     numberOfEvaluations;
    int     numberOfNodes;
};


#endif //IA_MINMAX_HPP
