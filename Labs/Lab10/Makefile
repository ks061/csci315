#
# CSCI 315 Operating Systems Design
# Author: L. Felipe Perrone
# Date: 2011-04-21
# Copyright (c) 2011 Bucknell University
#
# Permission is hereby granted, free of charge, to any individual or
# institution obtaining a copy of this software and associated
# documentation files (the "Software"), to use, copy, modify, and
# distribute without restriction, provided that this copyright and
# permission notice is maintained, intact, in all copies and supporting
# documentation.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL BUCKNELL UNIVERSITY BE LIABLE FOR ANY CLAIM, DAMAGES
# OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
# OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
# OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

# compiler
CC = gcc
CFLAGS = -std=gnu99 -Wall -g -pthread
EXECS = fdump file_stat read_dir traverse sender receiver 
INCLUDES = -I .
OBJS = hexdump.o
.PHONY: clean

all: $(EXECS)

hexdump.o: hexdump.c hexdump.h
	$(CC) $(CFLAGS) -c $< -o $@

fdump: fdump.c hexdump.o
	$(CC) $(CFLAGS) $^ -o $@

file_stat.o: file_stat.c
	$(CC) -c $(CFLAGS) file_stat.c

file_stat: file_stat.o
	$(CC) $(CFLAGS) -o file_stat file_stat.o

read_dir.o: read_dir.c
	$(CC) -c $(CFLAGS) read_dir.c

read_dir: read_dir.o
	$(CC) $(CFLAGS) -o read_dir read_dir.o

traverse.o: traverse.c
	$(CC) -c $(CFLAGS) traverse.c

traverse: traverse.o
	$(CC) $(CFLAGS) -o traverse traverse.o

sender: sender.c
	$(CC) $(CFLAGS) -o sender sender.c

receiver: receiver.c
	$(CC) $(CFLAGS) -o receiver receiver.c

clean:
	/bin/rm -f *~ *.o core $(EXECS) $(OBJS)
