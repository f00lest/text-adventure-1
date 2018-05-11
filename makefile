all: compile
	g++ -o zork_adventure main.o

compile:
	g++ -Wall -ggdb -O0 -c main.cpp

curses:
	g++ -o curses -lncurses curses.cpp