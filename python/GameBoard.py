##
## GameBoard.py
##

# Imports
import sys

# Macros
BOARD_SIZE = 18
BOARD_LENGTH = 324

# Class Game Board
class GameBoard:

	# Attributes
	board_1 = [ 0 for i in range(BOARD_LENGTH) ]
	board_2 = [ 0 for i in range(BOARD_LENGTH) ]

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
				sys.stdout.write(" " + str(i / BOARD_SIZE))
			if (self.board_1[i] == 1):
				sys.stdout.write("  x")
			elif (self.board_2[i] == 1):
				sys.stdout.write("  o")
			else:
				sys.stdout.write("  .")
		sys.stdout.write("\n")

	# Get All Possible Move
	def get_all_possible_move(player):
		moves = []

		if (player == 1):
			board = self.board_1
		elif (player == 2):
			board = self.board_2
		for i in range(BOARD_LENGTH):
			if (board[i] == 0):
				moves.append(i)
		return (moves)

	# Check Line
	def check_line(self, board, pos):
		print("> Start check")
		# check left
		win = 1
		for i in range(1, 5):
			if (((pos - i) / BOARD_SIZE) == (pos / BOARD_SIZE) and board[pos - i] == 0):
				win = 0
				break
		if (win):
			return (1)
		# check right
		win = 1
		for i in range(1, 5):
			if (((pos + i) / BOARD_SIZE) == (pos / BOARD_SIZE) and board[pos + i] == 0):
				win = 0
				break
		if (win):
			return (1)
		# check up
		win = 1
		for i in range(1, 5):
			if (((pos - (i * BOARD_SIZE)) % BOARD_SIZE) == (pos % BOARD_SIZE) and board[pos - (i * BOARD_SIZE)] == 0):
				win = 0
				break
		if (win):
			return (1)
		# check down
		win = 1
		for i in range(1, 5):
			if (((pos + (i * BOARD_SIZE)) % BOARD_SIZE) == (pos % BOARD_SIZE) and board[pos + (i * BOARD_SIZE)] == 0):
				win = 0
				break
		if (win):
			return (1)
		# check diag up right
		win = 1
		for i in range(1, 5):
			if (True and board[pos - (i * BOARD_SIZE) + i] == 0):
				win = 0
				break
		if (win):
			return (1)
		# check diag up left
		win = 1
		for i in range(1, 5):
			if (True and board[pos - (i * BOARD_SIZE) - i] == 0):
				win = 0
				break
		if (win):
			return (1)
		# check diag down left
		win = 1
		for i in range(1, 5):
			if (True and board[pos + (i * BOARD_SIZE) - i] == 0):
				win = 0
				break
		if (win):
			return (1)
		# check diag down right
		win = 1
		for i in range(1, 5):
			if (True and board[pos + (i * BOARD_SIZE) + i] == 0):
				win = 0
				break
		if (win):
			return (1)

	# Check Win
	def check_win(self, player):
		if (player == 1):
			board = self.board_1
		else:
			board = self.board_2
		for i in range(BOARD_LENGTH):
			if (board[i] == 1):
				if (self.check_line(board, i) == 1):
					return (1)
		return (0)


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
		return (0)

	# Init
	def __init__(self):
		pass
