CC=g++
CXXFLAGS=-Wall -I src
SRC_DIR=src
PERSONNE_DIR=Personne

all: Programme run

Chaine.o: Chaine.cpp

Programme.o: Programme.cpp

Personne.o: Personne.cpp

Programme: ${SRC_DIR}/Programme.o ${SRC_DIR}/Chaine.o   ${SRC_DIR}/${PERSONNE_DIR}/Personne.o
	${CC} ${CXXFLAGS} ${SRC_DIR}/Programme.o ${SRC_DIR}/Chaine.o ${SRC_DIR}/${PERSONNE_DIR}/Personne.o -o Programme

run:
	./Programme

.PHONY: clear
clean:
	rm -f ${SRC_DIR}/*.o
	rm -f Programme
	