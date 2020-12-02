CC=gcc
SRC=../src
EXECUTABLE=test
CFLAGS=-Wall -std=c99 -I$(SRC)
SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=)
INCLUDES=$(wildcard $(SRC)/*.h)
FUNCTIONS=$(INCLUDES:.h=.c)

.PHONY: all
all : $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	@echo "\033[31;1mLes fonctions tests compilent et s'éxécutent !\033[0m"

%: %.c $(INCLUDES) $(FUNCTIONS)
	$(CC) $(CFLAGS) $< $(FUNCTIONS) -o $@
	./$@

.PHONY : clean
clean :
	rm -f $(OBJECTS)
	rm -f *~
	rm -f \#*#
