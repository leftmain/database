F = -c -O3
all: a clean
clear:
	rm -f *.o a
a: main.o tree.o
	g++ main.o tree.o -o a
main.o: main.cpp tree.h
	g++ $F main.cpp
tree.o: tree.cpp tree.h bnode.h student.h
	g++ $F tree.cpp

