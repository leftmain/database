#ifndef NODE_H
#define NODE_h

#include "student.h"

class Node : public Student {
private:
	Node * left, * right;
public:
	Node(int value = 0) : Student(value) {
		left = right = 0;
	}
	Node(const Node& i) : Student(i) { left = right = 0; }
	~Node() { left = right = 0; }
	Node& operator=(const Node& rhs) {
		*((Student *)this) = rhs;
		left = right = 0;
		return *this;
	}
	Node * get_left() const { return left; }
	Node * get_right() const { return right; }
	void set_left(Node * l) { left = l; }
	void set_right(Node * r) { right = r; }
	void print() const {
		printf("%d\n", get_value());
	}
};

#endif

