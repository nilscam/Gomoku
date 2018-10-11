//
// Created by nils on 11/10/18.
//

#include "MinMax.hpp"

MinMax::MinMax(const TreeNode<Board> &tree) : tree(tree) {}

void MinMax::deepSimulation(TreeNode<Board> &parent) {
    auto childrens = parent.getChildrens();

    if (childrens.empty()) {
        // leaf
        Board   old(parent.getData());
        auto possiblesMoves = old.getPossiblesMoves();

        for (auto it : possiblesMoves) {
            old[it] = 1;//MIN OR MAX;
            old.prevMove = it;
            parent.addChildren(old);
            old[it] = 0;
        }
    } else {
        for (auto &child : childrens)
            deepSimulation(*child.get());
    }
}

void MinMax::retroPropagation(TreeNode<Board> &parent) {
    auto childrens = parent.getChildrens();

    if (childrens.empty()) {
        parent.value = evaluator.evaluate(parent.getData());
    } else {
        float   max = 0.0;
        for (auto &child : childrens)
            max = child->value > max ? child->value : max;
        parent.value = max;
    }
}

void MinMax::propagation() {
    deepSimulation(tree);
    retroPropagation(tree);

    std::cout << tree.value << std::endl;
    for (auto child : tree.getChildrens())
        std::cout << child->getData() << std::endl;
}

