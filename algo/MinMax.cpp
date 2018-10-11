//
// Created by nils on 11/10/18.
//

#include "MinMax.hpp"

void MinMax::deepSimulation(TreeNode<Board> *parent) {
    auto childrens = parent->getChildrens();

    if (childrens.empty()) {
        // leaf
        Board   old(parent->getData());
        auto possiblesMoves = old.getPossiblesMoves();

        for (auto it : possiblesMoves) {
            old.playOnCompressed(it, 1); //MIN OR MAX;
            old.prevMove = it;
            parent->addChildren(old);
            old.playOnCompressed(it, 1);
        }
    } else {
        for (auto &child : childrens)
            deepSimulation(child);
    }
}

void MinMax::retroPropagation(TreeNode<Board> *parent) {
    auto childrens = parent->getChildrens();

    if (childrens.empty()) {
        parent->value = evaluator.evaluate(parent->getData());
    } else {
        float   max = 0.0;
        for (auto &children : childrens) {
            retroPropagation(children);
            max = children->value > max ? children->value : max;
        }
        parent->value = max;
    }
}

void MinMax::propagation() {
    deepSimulation(&tree);
    deepSimulation(&tree);

    retroPropagation(&tree);
    return ;
}

