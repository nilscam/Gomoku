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
            auto copy = new TreeNode(old);

            copy->getData().play(it, 1); // MIN OR MAX
            copy->getData().prevMove = it;
            parent->addChildren(copy);
        }
    } else {
        for (auto &child : childrens)
            deepSimulation(child);
    }
}

void MinMax::retroPropagation(TreeNode<Board> *parent, MINMAX target) {
    auto childrens = parent->getChildrens();

    if (childrens.empty()) {
        parent->value = evaluator.evaluate(parent->getData());
    } else {
        if (target == MIN) {
            float   min = FLT_MIN;
            for (auto &children : childrens) {
                retroPropagation(children, MAX);
                min = children->value < min ? children->value : min;
            }
            parent->value = min;
        } else {
            float   max = FLT_MAX;
            for (auto &children : childrens) {
                retroPropagation(children, MIN);
                max = children->value > max ? children->value : max;
            }
            parent->value = max;
        }
    }
}

void MinMax::propagation() {
    deepSimulation(&tree);

    retroPropagation(&tree, MAX);

    for (auto child : tree.getChildrens())
        std::cout << child->getData() << std::endl;
}

