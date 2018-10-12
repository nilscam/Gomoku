//
// Created by nils on 12/10/18.
//

#include "MinMaxAlphaBeta.hpp"

void MinMax::deepSimulation(TreeNode<Board> *parent) {
    auto childrens = parent->getChildrens();

    if (childrens.empty()) {
        // leaf
        Board   old(parent->getData());
        auto possiblesMoves = old.getPossiblesMoves();

        for (auto it : possiblesMoves) {
            auto copy = new TreeNode(old);

            copy->getData().play(it, 1); // MIN OR MAX
            parent->addChildren(copy);
        }
    } else {
        for (auto &child : childrens)
            deepSimulation(child);
    }
}

void MinMaxAlphaBeta::deepSimulation(TreeNode<Node> *parent, Board board) {
    auto childrens = parent->getChildrens();

    if (childrens.empty()) {
        auto possiblesMoves = board.getPossiblesMoves();

        for (auto it : possiblesMoves) {
            auto copy = new TreeNode(old);

            copy->getData().play(it, 1); // MIN OR MAX
            parent->addChildren(copy);
        }
    } else {
        for (auto &child : childrens)
            deepSimulation(child);
    }
}

void MinMaxAlphaBeta::retroPropagation(TreeNode<Node> *parent, MINMAX) {

}

void MinMaxAlphaBeta::propagation() {

}

short MinMaxAlphaBeta::getBestMove() {
    return 0;
}

void MinMaxAlphaBeta::addMove(int, int) {

}

void MinMaxAlphaBeta::play() {

}

bool MinMaxAlphaBeta::timerEnd() {
    return false;
}

