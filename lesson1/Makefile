.PHONY: clean

all: main.o tools.o sorts.o
	g++ main.o tools.o sorts.o

main.o: main.cpp
	g++ -c main.cpp -g

tools.o: tools.cpp
	g++ -c tools.cpp -g

sorts.o: sorts.cpp
	g++ -c sorts.cpp -g
	
clean:
	rm -rf *.o *.out