.PHONY: clean

all: main.o tools.o sorts.o
	g++ main.o tools.o sorts.o

main.o: main.cpp
	g++ -c main.cpp

tools.o: tools.cpp
	g++ -c tools.cpp

sorts.o: sorts.cpp
	g++ -c sorts.cpp
	
clean:
	rm -rf *.o *.out