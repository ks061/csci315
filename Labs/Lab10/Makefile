CC = gcc
CFLAGS = -std=gnu99 -Wall -g #-DDEBUG
EXECS = fdump 
INCLUDES = -I .
OBJS = hexdump.o 
.PHONY: all clean

all: $(EXECS)

hexdump.o: hexdump.c hexdump.h
	$(CC) $(CFLAGS) -c $< -o $@

fdump: fdump.c hexdump.o
	$(CC) $(CFLAGS) $^ -o $@

clean:
	/bin/rm -rf $(EXECS) ${OBJS}
