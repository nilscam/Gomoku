//
// Created by nils on 11/10/18.
//

#ifndef IA_EVALUATOR_HPP
#define IA_EVALUATOR_HPP

#include "Board.hpp"

struct pattern {
    int size;
    float   value;
    float   lockerModifier;
};

class Evaluator {
public:
    Evaluator();
    ~Evaluator();

    float   evaluatePattern(Board &, pattern &);
    float   evaluate(Board &);

private:
    std::vector<pattern>    patterns = {
            {1, 1, 0},
            {2, 5, -2},
            {3, 25, 10},
            {4, 50, 20},
            {5, 999999, 0}
    };

};

#endif //IA_EVALUATOR_HPP
