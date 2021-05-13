CC=gcc
CFLAGS=-g -c -Wall -pedantic --std=c99

all: main

main: build/queue.o build/sort.o build/main.o
	$(CC) build/*.o -o main

build/queue.o: src/queue.c headers/header.h
	$(CC) $(CFLAGS) src/queue.c -o build/queue.o

build/sort.o: src/sort.c headers/header.h
	$(CC) $(CFLAGS) src/sort.c -o build/sort.o

build/main.o: main.c headers/header.h
	$(CC) $(CFLAGS) main.c -o build/main.o

clean:
	rm -rf build/*.o main
