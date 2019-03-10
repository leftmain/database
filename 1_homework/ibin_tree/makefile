F = -c -O3
all: a
a: main.o tree.o
	g++ main.o tree.o -o a
main.o: main.cpp tree.h
	g++ $F main.cpp
tree.o: tree.cpp tree.h node.h student.h
	g++ $F tree.cpp

clear:
	rm -f *.o a

