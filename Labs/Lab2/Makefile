CC = gcc
CFLAGS = -std=gnu99 -Wall -g #-DDEBUG

EXECS = pipes heap-test pipe-test tokens upper

all: $(EXECS)

heap-test: heap-test.c
	$(CC) $(CFLAGS) $< -o $@

pipes: pipes.c
	$(CC) $(CFLAGS) $< -o $@

pipe-test: pipe-test.c
	$(CC) $(CFLAGS) $< -o $@

tokens: tokens.c
	$(CC) $(CFLAGS) $< -o $@

upper: upper.c
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	/bin/rm -rf $(EXECS)
