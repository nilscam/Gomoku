#!/usr/bin/env python3

import math
import GameBoard as game

class MCTS:
    def __init__(self):
        #searcher
        self.Qsa = {} # sum des évaluations pour (state s, action a)
        self.Ns = {} # nombre de fois que j'ai été dans l'état s
        self.Nsa = {} # nombre de fois que j'ai choisi l'action a quand j'étais dans l'état s
        self.Ps = {} #policy returned by nn for state s

        self.coeffExplo = 1
        self.numMCTSSims = 20 # on fait 20 simulations de mtcs (training only)

    def clean(self):
        self.Nsa = {}
        self.Qsa = {}
        self.Ns = {}
        self.Ps = {}

    def pi(self, board, nnet):
        s = board.to_string()

        self.clean()
        for i in range(self.numMCTSSims):
            print (i)
            self.search(s, board.player_turn, nnet)

        counts = [ (self.Nsa[(s,a)] if (s,a) in self.Nsa else 0) for a in board.get_all_possible_move()]
        probs = [ x / float(sum(counts)) for x in counts]
        return probs


    # s est la string representation du board
    def search(self, s, player, nnet):
        board = game.GameBoard()
        board.load_state(s)
        board.player_turn = player

        if board.gameEnd():
            return 0 if board.reward == 0 else -1 # à changer

        if s not in P:
            v, self.Ps[s] = nnet.predict(board)
            self.Vs[s] = board.get_all_possible_move() # return a list of valid action
            self.Ns[s] = 0
            return -v


        # max ucb, best move
        max_u, best_action = -float("inf"), -1
        for action in self.Vs[s]:
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
        v = self.search(board.to_string(), board.player_turn, nnet)

        if (s, action) in self.Qsa:
            self.Qsa[(s, action)] = (self.Nsa[(s,action)] * self.Qsa[(s,action)] + v) / (self.Nsa[(s,action)] + 1) # on recalcul la moyenne des evaluations
            self.Nsa[(s, action)] += 1
        else:
            self.Qsa[(s,a)] = v
            self.Nsa[(s,a)] = 1

        self.Ns[s] += 1
        return -v
