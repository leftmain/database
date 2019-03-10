F = -O3 -c 

all: a

a: main.o matrix.o
	g++ main.o matrix.o -o a
main.o: main.cpp
	g++ $F main.cpp
matrix.o: matrix.cpp header.h
	g++ $F matrix.cpp

clear:
	rm *.o a

