all: 
	gcc -o proc code/proc.c
	gcc -o main code/main.c

proc:
	gcc -o proc code/proc.c

main:
	gcc -o main code/main.c
