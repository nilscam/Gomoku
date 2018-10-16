##
## test.py
##

# Imports
import sys
from GameBoard import GameBoard

file = open("infos.log", "w")
IN = "< "
OUT = "> "

# Write Log
def write_log(source, info):
	file.write(source + str(info) + "\n");

# Send Message
def snd_msg(msg):
	write_log(OUT, msg)
	print(msg)
	print("DEBUG - toto")

# Receive Message
def rcv_msg():
	msg = sys.stdin
	write_log(IN, msg)
	return (msg)

# Main
def main():
	game_board = GameBoard()

	game_board.play(1, 0, 10)
	game_board.play(2, 12, 1)
	game_board.play(1, 3, 4)
	game_board.display_board()
	return (0)

# Launcher
if __name__ == "__main__":
	main()
