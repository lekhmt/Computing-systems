all: 
	gcc -o encode code/encode.c
	gcc -o main code/main.c

encode:
	gcc -o encode code/encode.c

main:
	gcc -o main code/main.c
