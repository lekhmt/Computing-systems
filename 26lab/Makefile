CC=gcc
CFLAGS=-g -c -Wall -pedantic --std=c99

NAME=main
OBJECTS=$(patsubst src/%.c,build/%.o,$(wildcard src/*.c))
HEADERS=$(wildcard headers/*.h)

.PHONY: all clean

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) build/*.o -o $(NAME)

build/%.o: src/%.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@ 

clean:
	rm -rf build/*.o $(NAME)
