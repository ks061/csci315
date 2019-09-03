CC = gcc
CFLAGS = -std=gnu99 -Wall -g #-DDEBUG
EXECS = dlisttest
INCLUDES = -I .
OBJS = dnode.o dlist.o
.PHONY: all clean

all: $(EXECS)

dnode.o: dnode.c dnode.h 
	${CC} ${CFLAGS} -c $< -o $@

dlist.o: dlist.c dlist.h dnode.h
	${CC} ${CFLAGS} -c $< -o $@

dlisttest: dlisttest.c ${OBJS}
	${CC} ${CFLAGS} $< ${OBJS} -o $@

clean:
	/bin/rm -rf $(EXECS) ${OBJS}

