BIN_DIR = ./bin
INCLUDE_DIR = ./include
OBJ_DIR = ./obj
SRC_DIR = ./src

CC = gcc $(INCLUDES)
CFLAGS = -std=gnu99 -Wall -lrt -lpthread -g #DEBUG
EXECS = dp problem1 problem2
INCLUDES = -I $(INCLUDE_DIR)
OBJS = 
.PHONY: all clean

vpath %.h $(INCLUDE_DIR)
vpath %.c $(SRC_DIR)

all: $(EXECS)

dp: dp.c
	$(CC) $(CFLAGS) $< -o $@

problem1: problem1.c
	$(CC) $(CFLAGS) $< -o $@

problem2: problem2.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	/bin/rm -rf $(EXECS)
