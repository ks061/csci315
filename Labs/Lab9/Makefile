CC = gcc
CFLAGS = -std=gnu99 -Wall -g #-DDEBUG
EXECS = ishell 
INCLUDES = -I .
OBJS = wrappers.o
.PHONY: all clean

all: $(EXECS)

wrappers.o: wrappers.c wrappers.h
	$(CC) $(CFLAGS) -c $< -o $@

ishell: ishell.c $(OBJS)
	$(CC) $(CFLAGS) $< $(OBJS) -o $@

clean:
	/bin/rm -rf $(EXECS) ${OBJS}
