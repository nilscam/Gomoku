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
        old.compress();

        for (auto it : possiblesMoves) {
            old.playOnCompressed(it, 1); //MIN OR MAX;
            old.prevMove = it;
            parent.addChildren(old);
            old.playOnCompressed(it, 1);
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
        for (int i = 0; i < childrens.size(); i++) {
            retroPropagation(*childrens[i]);
            max = childrens[i]->value > max ? childrens[i]->value : max;
        }
        /*
        for (auto &child : childrens) {
            retroPropagation(*child.get());
            max = child->value > max ? child->value : max;
        }
         */
        parent.value = max;
    }
}

void MinMax::propagation() {
    deepSimulation(tree);
    std::cout << "first deep done" << std::endl;

    retroPropagation(tree);
    /*

    std::cout << tree.value << std::endl;

    for (auto child : tree.getChildrens())
        std::cout << child->getData() << std::endl;
    */
}

