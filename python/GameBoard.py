##
## GameBoard.py
##

# Imports
import sys

# Macros
BLACK = 1
WHITE = -1

BOARD_SIZE = 19
BOARD_LENGTH = 361

#fonctions à ajouter :
# toString: retourne une string representation de la position
# loadState: charge une position depuis une string
# toDataSet: transforme le board en dataSet

# Class GameBoard
class GameBoard:

	# Init
	def __init__(self):
		self.player_turn = BLACK
		self.reward = 0
		self.caseLeft = 361 # compteur quand il n'y a plus de place sur la map
		self.board_1 = [ 0 for i in range(BOARD_LENGTH) ]
		self.board_2 = [ 0 for i in range(BOARD_LENGTH) ]
		self.lastmove = -1

	# Display Board
	def display_board(self):
		sys.stdout.write("   ")
		for i in range(BOARD_SIZE):
			if (i < 10):
				sys.stdout.write(" ")
			sys.stdout.write(" " + str(i))
		sys.stdout.write("\n")
		sys.stdout.write("  0")
		for i in range(BOARD_LENGTH):
			if (i != 0 and i % BOARD_SIZE == 0):
				sys.stdout.write("\n")
				if (i / BOARD_SIZE < 10):
					sys.stdout.write(" ")
				sys.stdout.write(" " + str(int(i / BOARD_SIZE)))
			if (self.board_1[i] == 1):
				sys.stdout.write("  x")
			elif (self.board_2[i] == 1):
				sys.stdout.write("  o")
			else:
				sys.stdout.write("  .")
		sys.stdout.write("\n")

	# Get All Possible Move
	def get_all_possible_move(self):
		moves = []

		for i in range(BOARD_LENGTH):
			if (self.board_1[i] == 0 and self.board_2[i] == 0):
				moves.append(i)
		return (moves)

	def sumLign(self, board, pos, dir):
		sum = 0

		pos = [x + y for x, y in zip(pos, dir)]
		while all(cor >= 0 and cor < BOARD_SIZE for cor in pos) and board[pos[0] * BOARD_SIZE + pos[1]] == 1:
			pos = [x + y for x, y in zip(pos, dir)]
			sum += 1
		return sum

	def check_line(self, board, pos):
		dir = [[1, 0], [0, 1], [1, 1]]

		for d in dir:
			tp = [int(pos / BOARD_SIZE), pos % BOARD_SIZE]
			sum1 = self.sumLign(board, tp, d)
			sum2 = self.sumLign(board, tp, [x * y for x, y in zip(d, [-1, -1])])
			if sum1 + sum2 + 1 >= 5:
				return 1
		return 0

	# Check Win
	def check_win(self, player):
		if (player == 1):
			board = self.board_1
		else:
			board = self.board_2

		if self.lastmove != -1:
			return self.check_line(board, self.lastmove)
		# for i in range(BOARD_LENGTH):
		# 	if board[i] == 1 and self.check_line(board, i) == 1:
		# 			return (1)
		return 0

	def gameEnd(self):
		if self.check_win(self.player_turn * -1) == 1: # si il y a un gagant
			self.reward = BLACK if self.player_turn == WHITE else WHITE
			return 1
		elif self.caseLeft <= 0: # si il n'y a plus de case où jouer
			self.reward = 0
			return 1
		return 0

	# Correct Move
	def correct_move(self, pos):
		if (self.board_1[pos] == 1 or self.board_2[pos] == 1):
			return (0)
		return (1)

	# Play
	def play(self, pos):
		if (not self.correct_move(pos)):
			return (1)
		if (self.player_turn == BLACK):
			self.board_1[pos] = 1
		elif (self.player_turn == WHITE):
			self.board_2[pos] = 1
		self.player_turn *= -1
		self.caseLeft -= 1
		self.lastmove = pos

	# To String
	def to_string(self):
		board = ""

		for i in range(BOARD_LENGTH):
			if (self.board_1[i] == 1):
				board += "1"
			elif (self.board_2[i] == 1):
				board += "2"
			else:
				board += "0"
		return (board)

	# To DataSet
	def to_dataset(self):
		if self.player_turn == BLACK:
			return self.board_1 + self.board_2
		elif self.player_turn == WHITE:
			return self.board_2 + self.board_1

	# Load State
	def load_state(self, board):
		self.caseLeft = 361
		for i in range(BOARD_LENGTH):
			if (board[i] == "2"):
				self.board_1[i] = 0
				self.board_2[i] = 1
				self.caseLeft -= 1
			elif (board[i] == "1"):
				self.board_1[i] = 1
				self.board_2[i] = 0
				self.caseLeft -= 1
			else:
				self.board_1[i] = 0
				self.board_2[i] = 0
