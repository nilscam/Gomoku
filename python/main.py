##
## test.py
##

# Imports
import sys

file = open("C:\\User\\$9BS000-H5UFVKKH9ICS\\Desktop\\Gomoku\\python\\infos.log", "w")
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
	write_log(OUT, "Start Program")
	rcv_msg()
	snd_msg("OK")
	for msg in rcv_msg():
		snd_msg("OK")
	return (0)

# Launcher
if __name__ == "__main__":
	main()
