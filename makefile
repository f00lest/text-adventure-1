all: clear compile
	g++ -o text_adventure main.o

compile:
	g++ -Wall -ggdb -O0 -c main.cpp

clear:
	rm -f text_adventure
