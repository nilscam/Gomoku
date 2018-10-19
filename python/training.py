#!/usr/bin/env python3

import neuralnet as nn
import GameBoard as game

def playGame(nnet):
    examples = []
    mcts = MCTS()
    numMCTSSims = 20 # on fait 20 simulations de mtcs
    board = game.GameBoard()

    while True:
        mcts.clean()
        for i in range(numMCTSSims):
            mcts.search(board.toString(), nnet)

        examples.append([board, mcts.pi(s), None])
        a = random.choice(len(mcts.pi()), p=mcts.pi())
        board = board.play(a)
        if board.check_win():
            examples = assignRewards(examples, board)
            return examples


def training():
    threshold = 0.55 # after 55% winrate, change the neural net
    numGame = 100
    numIterations = 150

    nnet = nn.createModel()
    examples = []
    for i in range(numIterations):
        for e in range(numGame):
            examples += playGame(nnet)
        new_nnet = trainNNet(examples)
        frac_win = pit(new_nnet, nnet)
        if frac_win > threshold:
            nnet = new_nnet
    nn.save(nnet)
    return nnet
