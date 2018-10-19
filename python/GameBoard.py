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
	def get_all_possible_move():
		moves = []

		for i in range(BOARD_LENGTH):
			if (self.board_1[i] == 0 and self.board_2[i] == 0):
				moves.append(i)
		return (moves)

	# Check Line
	def check_line(self, board, pos):
		print("Check Line")
		""" Check Horizontal Line """
		nb_stone = 1	# nb stone aligned
		dir_1 = 1	# continue to check direction 1
		dir_2 = 1	# continue to check direction 2

		for i in range(1, 5):
			if (dir_1 and int((pos - i) / BOARD_SIZE) == int(pos / BOARD_SIZE) and board[pos - 1] == 1):
				nb_stone += 1
			else:
				dir_1 = 0
			if (dir_2 and int((pos + i) / BOARD_SIZE) == int(pos / BOARD_SIZE) and board[pos + 1] == 1):
				nb_stone += 1
			else:
				dir_2 = 0
		if (nb_stone >= 5):
			return (1)

		""" Check Vertical Line """
		nb_stone = 1	# nb stone aligned
		dir_1 = 1	# continue to check direction 1
		dir_2 = 1	# continue to check direction 2

		for i in range(1, 5):
			if (dir_1 and (pos - (i * BOARD_SIZE) > 0) and
					int((pos - (i * BOARD_SIZE)) % BOARD_SIZE) == int(pos % BOARD_SIZE) and
					(board[pos - (i * BOARD_SIZE)] == 1)):
				nb_stone += 1
			else:
				dir_1 = 0
			if (dir_2 and (pos + (i * BOARD_SIZE) < BOARD_LENGTH) and
					int((pos + (i * BOARD_SIZE)) % BOARD_SIZE) == int(pos % BOARD_SIZE) and
					(board[pos + (i * BOARD_SIZE)] == 1)):
				nb_stone += 1
			else:
				dir_2 = 0
		if (nb_stone >= 5):
			return (1)

		""" Check Diagonale """
		nb_stone = 1	# nb stone aligned
		dir_1 = 1	# continue to check direction 1
		dir_2 = 1	# continue to check direction 2

		for i in range(1, 5):
			if (dir_1 and (pos - (i * BOARD_SIZE) - i > 0) and
					((pos - (i * BOARD_SIZE) - i) % BOARD_SIZE) < (pos % BOARD_SIZE) and
					(board[pos - (i * BOARD_SIZE) - i] == 1)):
				nb_stone += 1
			else:
				dir_1 = 0
			if (dir_2 and (pos + (i * BOARD_SIZE) + i < BOARD_LENGTH) and
					((pos + (i * BOARD_SIZE) + i) % BOARD_SIZE) > (pos % BOARD_SIZE) and
					(board[pos + (i * BOARD_SIZE) + i] == 1)):
				nb_stone += 1
			else:
				dir_2 = 0
		if (nb_stone >= 5):
			return (1)

		""" Check Diagonale """
		nb_stone = 1	# nb stone aligned
		dir_1 = 1	# continue to check direction 1
		dir_2 = 1	# continue to check direction 2

		for i in range(1, 5):
			if (dir_1 and (pos - (i * BOARD_SIZE) + i > 0) and
					((pos - (i * BOARD_SIZE) + i) % BOARD_SIZE) > (pos % BOARD_SIZE) and
					(board[pos - (i * BOARD_SIZE) + i] == 1)):
				nb_stone += 1
			else:
				dir_1 = 0
			if (dir_2 and (pos + (i * BOARD_SIZE) - i < BOARD_LENGTH) and
					((pos + (i * BOARD_SIZE) - i) % BOARD_SIZE) < (pos % BOARD_SIZE) and
					(board[pos + (i * BOARD_SIZE) - i] == 1)):
				nb_stone += 1
			else:
				dir_2 = 0
		if (nb_stone >= 5):
			return (1)

	# Check Win
	def check_win(self, player):
		if (player == 1):
			board = self.board_1
		else:
			board = self.board_2
		for i in range(BOARD_LENGTH):
			if (board[i] == 1 and self.check_line(board, i) == 1):
					return (1)
		return (0)

	def gameEnd(self):
		if check_win == 1: # si il y a un gagant
			self.reward = BLACK if board.player_turn == WHITE else WHITE
			return 1
		elif self.caseLeft <= 0: # si il n'y a plus de case où jouer
			self.reward = 0
			return 1
		return 0

	# Correct Move
	def correct_move(self, x, y):
		if (self.board_1[y * BOARD_SIZE + x] == 1 or self.board_2[y * BOARD_SIZE + x] == 1):
			return (0)
		return (1)

	# Play
	def play(self, player, x, y):
		if (not self.correct_move(x, y)):
			return (1)
		if (player == 1):
			self.board_1[y * BOARD_SIZE + x] = 1
		elif (player == 2):
			self.board_2[y * BOARD_SIZE + x] = 1
		self.check_win(1)
		self.player_turn *= -1
		self.caseLeft -= 1
		return (0)

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
		if (self.player_turn == BLACK)
			return (self.board_1 + self.board_2)
		elif (self.player_turn == WHITE)
			return (self.board_2 + self.board_1)

	# Load State
	def load_state(self, board):
		for i in range(BOARD_LENGTH):
			if (board[i] == "2"):
				self.board_1[i] == 0
				self.board_2[i] == 1
			elif (board[i] == "1"):
				self.board_1[i] == 1
				self.board_2[i] == 0
			else:
				self.board_1[i] == 0
				self.board_2[i] == 0
