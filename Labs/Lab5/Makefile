CC = gcc
CFLAGS = -std=gnu99 -Wall -lrt -lpthread -g #DEBUG
EXECS = adt-test 
INCLUDES = -I .
OBJS = 
.PHONY: all clean

BIN_DIR = ./bin
INCLUDE_DIR = ./include
OBJ_DIR = ./obj
SRC_DIR = ./src

all: $(EXECS)

$(OBJ_DIR)/circular-list.o: $(SRC_DIR)/circular-list.c $(INCLUDE_DIR)/circular-list.h
	$(CC) $(CFLAGS) -c $< -o $@

adt-test: $(SRC_DIR)/adt-test.c $(OBJ_DIR)/circular-list.o
	$(CC) $(CFLAGS) $^ -o $(BIN_DIR)/adt-test

clean:
	/bin/rm -rf $(EXECS) $(OBJS)
