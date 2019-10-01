CC = gcc
CFLAGS = -std=gnu99 -Wall -g #DEBUG
EXECS = echod echoreq echoreq2
INCLUDES = -I .
OBJS = wrappers.o
.PHONY: all clean

all: $(EXECS)

echod: echod.c $(OBJS)
	$(CC) $(CFLAGS) $< ${OBJS} -o $@

echoreq: echoreq.c $(OBJS)
	$(CC) $(CFLAGS) $< ${OBJS} -o $@

echoreq2: echoreq2.c $(OBJS)
	$(CC) $(CFLAGS) $< ${OBJS} -o $@

wrappers.o: wrappers.c wrappers.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	/bin/rm -rf $(EXECS) $(OBJS)
