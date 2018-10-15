//
// Created by nils on 11/10/18.
//

#include "MinMax.hpp"

// appeler la fonction avec a = -infinie et b = +infinie
float MinMax::alphaBeta(TreeNode<Board> *node, float a, float b, MINMAX target) {
    auto childrens = node->getChildrens();

    if (childrens.empty()) { // si c'est une feuille on retourne la valeur du noeud
        node->value = evaluator.evaluate(node->getData());
        numberOfEvaluations += 1; // pour les stats
        return node->value;
    } else if (target == MIN) {
        float   v = FLT_MAX;
        bool    brk = false;

        for (int i = 0; i < childrens.size(); i++) {
            v = std::min(v, alphaBeta(childrens[i], a, b, SWITCH_TARGET(target)));
            if (a >= v) { // coupure
                //node->deleteFrom(i); ne marche pas pour l'instant
                return v;
            }
            b = std::min(v, b);
            if (timerEnd()) {
                brk = true;
                break;
            }
        }
        if (!brk)
            node->value = v;
        return v;
    } else if (target == MAX) {
        float v = FLT_MIN;
        bool    brk = false;

        for (int i = 0; i < childrens.size(); i++) {
            v = std::max(v, alphaBeta(childrens[i], a, b, SWITCH_TARGET(target)));
            if (v >= b) { // coupure
                //node->deleteFrom(i); ne marche pas pour l'instant
                return v;
            }
            a = std::max(a, v);
            if (timerEnd()) {
                brk = true;
                break;
            }
        }
        if (!brk)
            node->value = v;
        return v;
    }
    std::cerr << "ERREUR ALPHABETA" << std::endl;
    return 0.0;
}

void MinMax::deepSimulation(TreeNode<Board> *parent, TURN player) {
    auto childrens = parent->getChildrens();

    if (childrens.empty()) {
        // leaf
        Board   old(parent->getData());
        auto possiblesMoves = old.getPossiblesMoves();

        for (auto it : possiblesMoves) {
            auto copy = new TreeNode(old);

            copy->getData().play(it, player); // MIN OR MAX
            parent->addChildren(copy);
            numberOfNodes += 1;
        }
    } else {
        for (auto &child : childrens) {
            deepSimulation(child, SWITCH_PLAYER(player));
            if (timerEnd())
                break;
        }
    }
}

void MinMax::retroPropagation(TreeNode<Board> *parent, MINMAX target) {
    auto childrens = parent->getChildrens();

    if (childrens.empty()) {
        parent->value = evaluator.evaluate(parent->getData());
    } else {
        if (target == MIN) {
            float   min = FLT_MAX;
            for (auto &children : childrens) {
                retroPropagation(children, MAX);
                min = children->value < min ? children->value : min;
                if (timerEnd())
                    break;
            }
            parent->value = min;
        } else {
            float   max = FLT_MIN;
            for (auto &children : childrens) {
                retroPropagation(children, MIN);
                max = children->value > max ? children->value : max;
                if (timerEnd())
                    break;
            }
            parent->value = max;
        }
    }
}

/* inutile pour l'instant */
void MinMax::reduceTree(TreeNode<Board> *node, MINMAX target) {
    auto childrens = node->getChildrens();

    std::vector<float>  results;
    for (auto &child : childrens)
        results.push_back(child->value);
    std::sort(results.begin(), results.end());
}

short MinMax::getBestMove() {
    timer = clock();

    curDeep = 0;
    numberOfEvaluations = 0;
    numberOfNodes = 0;
    tree = new TreeNode(curPlate);
    while (!timerEnd()) {
        std::cout << "deep: " << curDeep << std::endl;
        deepSimulation(tree, WHITE);
        if (timerEnd())
            break;
        alphaBeta(tree, FLT_MIN, FLT_MAX, MAX);
        if (timerEnd())
            break;
        //retroPropagation(tree, MAX);
        curDeep += 1;
    }
    short move = 0;
    float best = FLT_MIN;

    for (auto child : tree->getChildrens())
        if (best < child->value) { // on recherche le move avec la plus haute valeur
            move = child->getData().last_play;
            best = child->value;
        }
    delete tree;
    return move;
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

void MinMax::debugMinMax() {
    std::cout << "DEBUG - <number of nodes explored: " << numberOfNodes << ">, <number of evaluations made: " << numberOfEvaluations << ">" << std::endl;
}

