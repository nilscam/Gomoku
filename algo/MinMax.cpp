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
    deepSimulation(&tree);

    retroPropagation(&tree, MAX);

    for (auto child : tree.getChildrens().back()->getChildrens())
        std::cout << child->getData() << std::endl;
}

short MinMax::getBestMove() {
    timer = clock();

    curDeep = 0;
    tree = TreeNode(curPlate);
    while (!timerEnd()) {
        std::cout << "deep" << std::endl;
        deepSimulation(&tree);
        retroPropagation(&tree, MAX);
    }
    return 0;
}

void MinMax::play() {
    if (firstMove) {
        std::cout << "9,9" << std::endl; // on joue au milieu le premier move
        curPlate.play(POS(9, 9), WHITE);
    } else {
        short   pos_to_play = getBestMove();

        std::cout << pos_to_play / HEIGHT << "," << pos_to_play % WIDTH << std::endl;
        curPlate.play(pos_to_play, WHITE);
    }
}

void MinMax::addMove(int y, int x) {
    firstMove = false;
    curPlate.play(POS(y, x), BLACK);
}

bool MinMax::timerEnd() {
    return ((double)(clock() - timer) / CLOCKS_PER_SEC) > 4.5;
}

