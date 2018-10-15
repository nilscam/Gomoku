##
## test.py
##

# Imports
import sys

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
	write_log(OUT, "Start Program")
	rcv_msg()
	snd_msg("UNKNOWN")
	rcv_msg()
	snd_msg("OK")
	snd_msg("5,5")
	for msg in rcv_msg():
		snd_msg("5,5")
	return (0)

# Launcher
if __name__ == "__main__":
	main()
