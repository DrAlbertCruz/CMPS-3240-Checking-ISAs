CC=gcc
FLAGS=-Wall -O0 -msse -mavx

all: main.out

main.out: main.o myblas.o
	${CC} ${FLAGS} -o $@ $^

main.o: main.c myblas.h
	${CC} ${FLAGS} -o $@ -c $<

myblas.o: myblas.c
	${CC} ${FLAGS} -o $@ -c $<
