CC=gcc
FLAGS=-Wall -O0 -msse -mavx -std=c99
# Relevant flags here:
#	-msse: The flag to enable the SSE intrinsics for gcc. Strangely, on my
#	macbook it still reads as SSE enabled whether I include this flag or
#	not.
#
#	-mavx: The flag to enable AVX intrinsics for gcc. Needed, unlike -msse.

all: main.out

main.out: main.o myblas.o
	${CC} ${FLAGS} -o $@ $^

main.o: main.c myblas.h
	${CC} ${FLAGS} -o $@ -c $<

myblas.o: myblas.c
	${CC} ${FLAGS} -o $@ -c $<

clean: 
	rm -f *.out *.o
