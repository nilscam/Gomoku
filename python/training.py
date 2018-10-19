#!/usr/bin/env python3

import neuralnet as nn
import GameBoard as game

BLACK = 1
WHITE = -1

def assignRewards(examples, board):
    return 1

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

        while board.gameEnd():

            if colorNet1 == board.player_turn:
                moves = mtcs.pi(board.toString(), board.player_turn, net1)
            else:
                moves = mtcs.pi(board, board.player_turn, net2)
            a = max(moves) # le move joué est le move le mieu évalué
            board = board.play(a)

        if board.player_turn == 1


def playGame(nnet):
    examples = []
    mcts = MCTS()
    board = game.GameBoard()

    while True:
        moves = mtcs.pi(board, board.player_turn, nnet)

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

    nnet = nn.neuralnet()
    examples = []
    for i in range(numIterations):
        for e in range(numGame):
            examples += playGame(nnet)

        new_nnet = nn.neuralNet()
        new_nnet.copy(nnet)
        new_nnet.train(examples)

        winrate = fight(new_nnet, nnet) # on fait combattre l'ancien réseau de neuronnes avec le nouveau

        if winrate > threshold:
            nnet = new_nnet
    nnet.save(nnet)
    return nnet
