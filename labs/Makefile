all: main.o calc.o check.o
	gcc main.o calc.o check.o -g -Wall
main.o: main.c
	gcc -c main.c -g -Wall
calc.o: calc.c
	gcc -c calc.c -g -Wall
check.o: check.c
	gcc -c check.c -g -Wall
run_norm:
	./a.out 41 + 33 111 - 8 22 "*" 5 221 % 111 100 + 13 -k 2
run_er:
	./a.out 112 1234 1_1 -k 2
