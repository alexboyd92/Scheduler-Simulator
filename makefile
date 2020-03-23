CC=gcc
CFLAGS = -g -Wall -pedantic -std=c11

a2: a2.o printStats.o queue.o cpu.o
a2.o:a2.h queue.h cpu.h
queue.o: queue.h a2.h

test:
		 ./a2
clean:
		rm -f *.o a2 core
