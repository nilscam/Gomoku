#!/usr/bin/env python3

from random import randint
import neuralnet as nn
from mcts import MCTS
import GameBoard as game

import numpy as np

BLACK = 1
WHITE = -1

# on fait combattre 2 réseaux de neuronnes l'un contre l'autre et on retourne le pourcentage de win du premier sur le deuxième
def fight(net1, net2):
    numGame = 10
    win_net1 = 0
    win_net2 = 0
    mcts = MCTS()

    for color in [BLACK, WHITE]:
        for e in range(int(numGame / 2)):
            print ('[FIGHTING] game number ', e)
            board = game.GameBoard()
            board.play(randint(0, 360)) # on part d'une position random
            while not board.gameEnd():

                if board.player_turn == color:
                    moves = mcts.pi(board, net1)
                else:
                    moves = mcts.pi(board, net2)
                a = moves.index(max(moves))
                board.play(a)
            print ('end, winner = ', "White" if board.reward == -1 else "Black")
            board.display_board()

            if board.player_turn == color: #le nouveau réseau a perdu
                win_net2 += 1
            else:
                win_net1 += 1

    print ('bilan de l\'affrontement: ', win_net1, ' / ', win_net2)

    return win_net1 / numGame

def assignRewards(examples, board):
    reward = -board.reward # normalement reward = board.reward mais on a joué le premier coup random

    for ex in examples:
        ex[2] = reward
        reward *= -1
    return examples

def playGame(nnet):
    examples = []
    mcts = MCTS()
    board = game.GameBoard()

    board.play(randint(0, 360))
    while True:
        moves = mcts.pi(board, nnet)

        # ajouter un getSymetrie (on flip et reverse le board dans tous les sens pour + de dataSet)
        examples.append([board.to_dataset(), moves, None])
        a = np.random.choice(len(moves), p=moves)
        #a = moves.index(max(moves)) # le move joué est le move le mieu évalué
        board.play(a)

        if board.gameEnd(): # à ajouter
            board.display_board()
            examples = assignRewards(examples, board)
            return examples

def training():
    threshold = 0.55 # after 55% winrate, change the neural net
    numGame = 10
    numIterations = 100

    nnet = nn.neuralNet()
    for i in range(numIterations):
        examples = []
        for e in range(numGame):
            print ('[TRAINING] game number ', e)
            examples += playGame(nnet)

        nnet.train(examples)
        nnet.save()

        # new_nnet = nn.neuralNet()
        # print ('copying neural net')
        # new_nnet.copy(nnet)
        # print ('training nn')
        # new_nnet.train(examples)
        #
        # print ('fighting')
        # winrate = fight(new_nnet, nnet) # on fait combattre l'ancien réseau de neuronnes avec le nouveau
        # print ('winrate from new on old is ', winrate)
        #
        # if winrate > threshold:
        #     print ('nnet replaced')
        #     nnet = new_nnet

    nnet.save()
    return nnet
