#!/usr/bin/env python3

import math
import GameBoard as game

class evaluator:
    def __init__(self):
        #searcher
        Qsa = {} # sum des évaluations pour (state s, action a)
        Ns = {} # nombre de fois que j'ai été dans l'état s
        Nsa = {} # nombre de fois que j'ai choisi l'action a quand j'étais dans l'état s
        Ps = {} #policy returned by nn for state s

        coeffExplo = 1

    def clean():
        Nsa = {}
        Qsa = {}
        Ns = {}
        Ps = {}

    # s est la string representation du board
    def search(self, s, player, nnet):
        if board.check_win():
            return -board.reward() # à changer

        board = game.Board()
        board.loadState(s, player)

        if s not in P:
            self.Ps[s], v = nnet.predict(s)
            self.Vs[s] = board.get_all_possible_move() # return a list of valid action
            self.Ns[s] = 0
            return -v


        # max ucb, best move
        max_u, best_action = -float("inf"), -1
        for action in Vs[s]):
            #value function
            if (s, action) in self.Qsa:
                u = self.Qsa[(s, action)] + self.coeffExplo * self.Ps[s][action] * (math.sqrt(self.Ns[s]) / (1 + self.Nsa[(s,action)])) # coeffExplo = 1
            else:
                u = self.coeffExplo * self.Ps[s][action] * math.sqrt(self.Ns[s] + 1e-8) # 1e-8 pour ne pas crash quand ns vaut 0

            if u > max_u:
                max_u = u
                best_action = action

        action = best_action
        board.play(action)
        v = search(board.toString(), board.player, nnet)

        if (s, action) in self.Qsa:
            self.Qsa[(s, action)] = (self.Nsa[(s,action)] * self.Qsa[(s,action)] + v) / (self.Nsa[(s,action)] + 1) # on recalcul la moyenne des evaluations
            self.Nsa[(s, action)] += 1
        else:
            self.Qsa[(s,a)] = v
            self.Nsa[(s,a)] = 1

        self.Ns[s] += 1
        return -v
