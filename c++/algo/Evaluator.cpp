//
// Created by nils on 11/10/18.
//

#include "Evaluator.hpp"

Evaluator::Evaluator() = default;

Evaluator::~Evaluator() = default;

float Evaluator::evaluatePattern(Board &board, pattern &pat) {
    float   score = 0;

    for (int y = board.playingZone[0]; y < board.playingZone[0] + board.playingZone[2]; y++) {
        for (int x = board.playingZone[1]; x < board.playingZone[1] + board.playingZone[1]; x++) {

        }
    }

}

/* return the score for white: positiv if white as advantage, negative otherwise */
float Evaluator::evaluate(Board &toEvaluate) {
    float score = 0;
    toEvaluate.decompress();

    for (pattern &pat : patterns) {
        score += evaluatePattern(toEvaluate, pat);
    }
    return score;
}
