#!/usr/bin/env python3

import neuralnet as nn
from mcts import MCTS
import GameBoard as game

BLACK = 1
WHITE = -1

# on fait combattre 2 réseaux de neuronnes l'un contre l'autre et on retourne le pourcentage de win du premier sur le deuxième
def fight(net1, net2):
    numGame = 100
    colorNet1 = 1
    win_net1 = 0
    win_net2 = 0
    mcts = MCTS()

    for e in range(numGame):

        # playgame
        board = game.GameBoard()
        while not board.gameEnd():

            if colorNet1 == board.player_turn:
                moves = mcts.pi(board, net1)
            else:
                moves = mcts.pi(board, net2)
            a = max(moves) # le move joué est le move le mieu évalué
            board = board.play(a)

        if board.player_turn == BLACK: # black lost
            if colorNet1 == BLACK:
                win_net2 += 1
            else:
                win_net1 += 1
        elif board.player_turn == WHITE: # white lost
            if colorNet1 == WHITE:
                win_net2 += 1
            else:
                win_net1 += 1

        colorNet1 = colorNet1 * -1

    return win_net1 / numGame

def assignRewards(examples, board):
    reward = board.reward

    for ex in examples:
        ex[2] = reward
        reward *= -1
    return examples

def playGame(nnet):
    examples = []
    mcts = MCTS()
    board = game.GameBoard()

    while True:
        moves = mcts.pi(board, nnet)

        examples.append([board.toDataSet(), moves, None])
        a = max(moves) # le move joué est le move le mieu évalué
        board = board.play(a)

        if board.gameEnd(): # à ajouter
            examples = assignRewards(examples, board)
            return examples

def training():
    threshold = 0.55 # after 55% winrate, change the neural net
    numGame = 100
    numIterations = 150

    nnet = nn.neuralNet()
    examples = []
    for i in range(numIterations):
        for e in range(numGame):
            print ("playing game")
            examples += playGame(nnet)

        new_nnet = nn.neuralNet()
        new_nnet.copy(nnet)
        new_nnet.train(examples)

        winrate = fight(new_nnet, nnet) # on fait combattre l'ancien réseau de neuronnes avec le nouveau

        if winrate > threshold:
            nnet = new_nnet

    nnet.save(nnet)
    return nnet
