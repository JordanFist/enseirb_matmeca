CC=g++
CXXFLAGS=-Wall

all: Programme run

Chaine.o: Chaine.cpp

Programme.o: Programme.cpp

Programme: Programme.o Chaine.o

run:
	./Programme

.PHONY: clear
clear:
	rm -f *.o
	rm -f Programme
	