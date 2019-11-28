CC = gcc -I ./include
CFLAGS = -std=gnu99 -Wall -g #-DDEBUG

INC = ./include
SRC = ./src
OBJ = ./obj
DOC = ./doc
BIN = ./bin

vpath %.h ./include
vpath %.c ./src

EXECS = frag-eval frag-eval-exp

all: $(EXECS)

doc:
	doxygen

$(OBJ)/dnode.o: dnode.h dnode.c
	$(CC) $(CFLAGS) -c $(SRC)/dnode.c -o $(OBJ)/dnode.o

$(OBJ)/dlist.o: dlist.h dlist.c dnode.h
	$(CC) $(CFLAGS) -c $(SRC)/dlist.c -o $(OBJ)/dlist.o

dlisttest: $(SRC)/dlisttest.c $(OBJ)/dnode.o $(OBJ)/dlist.o
	$(CC) $(CFLAGS) $(OBJ)/dnode.o $(OBJ)/dlist.o $(SRC)/dlisttest.c -o $(BIN)/dlisttest

$(OBJ)/allocator.o: allocator.c allocator.h dlist.h
	$(CC) $(CFLAGS) -c $< -o $@

frag-eval: $(SRC)/frag-eval.c $(OBJ)/allocator.o $(OBJ)/dlist.o $(OBJ)/dnode.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

frag-eval-exp: $(SRC)/frag-eval-exp.c $(OBJ)/allocator.o $(OBJ)/dlist.o $(OBJ)/dnode.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

.PHONY: clean
clean:
	/bin/rm -rf $(BIN)/* $(OBJ)/* core* *~

