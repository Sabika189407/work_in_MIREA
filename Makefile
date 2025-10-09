all: train1.o
	gcc train1.o -g
train1.o:
	gcc -c train1.c
clean:
	rm -rf *.o a.out
