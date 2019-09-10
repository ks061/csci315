CC = gcc
CFLAGS = -std=gnu99 -Wall -g #-DDEBUG

EXECS = catcount cmds cmdreverse fork fork-file fork-wait myprog

.PHONY: all clean

all: $(EXECS)

catcount: catcount.c
	$(CC) $(CFLAGS) $< -o $@

cmds: cmds.c
	$(CC) $(CFLAGS) $< -o $@

cmdreverse: cmdreverse.c
	$(CC) $(CFLAGS) $< -o $@

fork: fork.c
	$(CC) $(CFLAGS) $< -o $@	

fork-file: fork-file.c
	$(CC) $(CFLAGS) $< -o $@

fork-wait: fork-wait.c
	$(CC) $(CFLAGS) $< -o $@

myprog: myprog.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	/bin/rm -rf $(EXECS)

