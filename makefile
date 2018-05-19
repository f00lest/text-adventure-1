all: compile
	g++ -o text_adventure main.o

compile:
	g++ -Wall -ggdb -O0 -c main.cpp
