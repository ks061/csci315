CC = gcc
CFLAGS = -std=gnu99 -Wall -g #-DDEBUG

EXECS = char-threads mytime summation summation3 summation4

all: $(EXECS)

char-threads: char-threads.c
	$(CC) $(CFLAGS) -pthread $< -o $@

mytime: mytime.c
	$(CC) $(CFLAGS) $< -o $@

summation: summation.c
	$(CC) $(CFLAGS) -lpthread -lm $< -o $@

summation3: summation3.c
	$(CC) $(CFLAGS) -lpthread -lm $< -o $@

summation4: summation4.c
	$(CC) $(CFLAGS) -lpthread -lm $< -o $@

.PHONY: clean
clean:
	/bin/rm -rf $(EXECS)
