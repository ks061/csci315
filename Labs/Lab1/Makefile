CC = gcc
CFLAGS = -std=gnu99 -Wall -g #-DDEBUG
EXECS = cmdreverse cmds fork fork-data fork-test myprog
INCLUDES = -I .
.PHONY: all clean

all: $(EXECS)

cmdreverse: cmdreverse.c
	${CC} ${CFLAGS} $< -o $@

cmds: cmds.c
	${CC} ${CFLAGS} $< -o $@

myprog: myprog.c
	${CC} ${CFLAGS} $< -o $@

clean:
	/bin/rm -rf $(EXECS)

