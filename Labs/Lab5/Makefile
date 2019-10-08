BIN_DIR = ./bin
INCLUDE_DIR = ./include
OBJ_DIR = ./obj
SRC_DIR = ./src

CC = gcc $(INCLUDES)
CFLAGS = -std=gnu99 -Wall -lrt -lpthread -g #DEBUG
EXECS = adt-test prodcons 
INCLUDES = -I $(INCLUDE_DIR)
OBJS = 
.PHONY: all clean

vpath %.h $(INCLUDE_DIR)
vpath %.c $(SRC_DIR)

all: makedirs $(EXECS)

makedirs:
	mkdir -p $(BIN_DIR) $(OBJ_DIR)

$(OBJ_DIR)/circular-list.o: $(SRC_DIR)/circular-list.c $(INCLUDE_DIR)/circular-list.h
	$(CC) $(CFLAGS) -c $< -o $@

adt-test: $(SRC_DIR)/adt-test.c $(OBJ_DIR)/circular-list.o
	$(CC) $(CFLAGS) $^ -o $(BIN_DIR)/$@

prodcons: $(SRC_DIR)/prodcons.c $(OBJ_DIR)/circular-list.o
	$(CC) $(CFLAGS) $^ -o $(BIN_DIR)/$@

clean:
	/bin/rm -rf $(OBJ_DIR) $(BIN_DIR)
