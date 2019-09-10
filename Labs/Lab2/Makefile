CC = gcc
CFLAGS = -std=gnu99 -Wall -g #-DDEBUG

EXECS = heap-test pipe-test

all: $(EXECS)

heap-test: heap-test.c
	$(CC) $(CFLAGS) $< -o $@

pipe-test: pipe-test.c
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	/bin/rm -rf $(EXECS)
