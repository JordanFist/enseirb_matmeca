CXXFLAGS=-Wall

all: prog run

prog: Chaine.o Programme.o 
	g++ ${CXXFLAGS} $^ -o $@

Programme.o: Chaine.hpp

run:
	clear
	./prog

clean:
	rm -f *.o prog