SRC_DIR = src
TST_DIR = tst
BUILD_DIR = build

C_SRC_FILES = $(wildcard ${SRC_DIR}/*.c)
C_TST_FILES = $(wildcard ${TST_DIR}/*.c)
OBJ_FILES = $(patsubst %.c, %.o, ${C_SRC_FILES} ${C_TST_FILES})

CC = gcc
FLAGS = -Wall -g

TAB = y.tab.h y.tab.c

all: parse

clean:
	rm -f ${BUILD_DIR}/*
	rm -f parse
	rm -f test

grammar:
	bison -y -d ${SRC_DIR}/myml.y
	mv ${TAB} ${BUILD_DIR}

pattern:
	lex ${SRC_DIR}/myml.l
	mv lex.yy.c ${BUILD_DIR}
	
%.o: %.c
	${CC} ${FLAGS} -o ${BUILD_DIR}/$(notdir $@) -c $^

parse: grammar pattern ${OBJ_FILES}
	${CC} ${FLAGS} -I ${SRC_DIR} ${BUILD_DIR}/* -o $@  

test: ${BUILD_DIR}/main_test.c
	${CC} ${FLAGS} ${BUILD_DIR}/main_test.c -o $@


