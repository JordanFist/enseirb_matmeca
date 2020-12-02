EXECUTABLE=main
CC=gcc
CFLAGS=-Wall -std=c99
SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)

.PHONY: all
all : $(EXECUTABLE) 

$(EXECUTABLE) : $(OBJECTS) 

card.o: card.c card.h

player.o: player.c card.h player.h

board.o: board.c card.h player.h board.h

.PHONY: clean
clean :
	rm -f $(OBJECTS)
	rm -f *~
	rm -f \#*#
