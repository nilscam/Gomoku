//
// Created by nils on 11/10/18.
//

#ifndef IA_EVALUATOR_HPP
#define IA_EVALUATOR_HPP

#include "Board.hpp"

class Evaluator {
public:
    Evaluator();
    ~Evaluator();

    float   evaluate(const Board &);

private:

};


#endif //IA_EVALUATOR_HPP
