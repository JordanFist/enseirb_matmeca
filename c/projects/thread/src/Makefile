CC=gcc
FLAGS=-Wall -Wextra -g -O3 -Wno-deprecated-declarations
EXE=main
BLD_DIR=../build
.PHONY: all
all: build run

thread.o: thread.c
	${CC} -c ${FLAGS} $^ -o ${BLD_DIR}/$@

example.o: example.c
	${CC} -c ${FLAGS} $^ -o ${BLD_DIR}/$@

build: thread.o example.o
	cd ${BLD_DIR} && \
	${CC} ${FLAGS} $^ -o ${EXE}
run: 
	./${BLD_DIR}/${EXE}


