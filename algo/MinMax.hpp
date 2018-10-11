//
// Created by nils on 11/10/18.
//

#ifndef IA_MINMAX_HPP
#define IA_MINMAX_HPP

#include "Board.hpp"
#include "TreeNode.tpp"
#include "Evaluator.hpp"

class MinMax {
public:
    MinMax() = default;

    // we propagate all the moves on the tree
    void    deepSimulation(TreeNode<Board> *);
    // we evaluate nodes and process backpropagation
    void    retroPropagation(TreeNode<Board> *);

    void    propagation();

private:
    TreeNode<Board>   tree;

    Evaluator   evaluator;
    short   curDeep;
};


#endif //IA_MINMAX_HPP
