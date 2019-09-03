CC = gcc
CFLAGS = -std=gnu99 -Wall -g #-DDEBUG
EXECS = dlisttest
INCLUDES = -I .
OBJS = dnode.o dlist.o
.PHONY: all clean

all: $(EXECS)

dnode.o: dnode.c dnode.h 
	${CC} ${CFLAGS} ${INCLUDES} -c denode.c

dlist.o: dlist.h dlist.c dnode.h
	${CC} ${CFLAGS} ${INCLUDES} -c dlist.c

dlisttest: ${OBJS}
	${CC} ${CLFAGS} ${OBJS} -o $@

clean:
	/bin/rm -rf $(EXECS) ${OBJS}

