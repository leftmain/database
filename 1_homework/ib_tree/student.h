#include <stdio.h>
#include <string.h>

#define LEN 1024

class Student
{
private:
	int value;
public:
	Student(int v = 0) { value = v; }
	Student(const Student& i) { value = i.value; }
	~Student() { value = 0; }
	Student& operator=(const Student& rhs) {
		value = rhs.value;
		return *this;
	}
	int operator<(const Student& b) const {
		return value - b.value;
	}
	void swap(Student& b) {
		int v = value;
		value = b.value;
		b.value = v;
	}
	int get_value() const { return value; }
	int read(FILE * fp) {
		if (fscanf(fp, "%d", &value) != 1) return -2;
		return 0;
	}
	void clear() {
		value = 0;
	}
	void print() { printf("%d\n", value); }
	void print_() { printf("[ %d ] ", value); }
};

