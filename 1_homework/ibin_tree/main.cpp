#include "tree.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char ** argv) {
	Tree tree;
	int k = 0;
	int res = 0;
	double t = 0.;
	const char * filename = "a.txt";

	if (argc != 2) {
		printf("usage: %s [filename]\n", argv[0]);
		return -1;
	}
	if (argc == 2) filename = argv[1];

	printf("Reading tree...\n");
	t = clock();
	if ((res = tree.read(filename))) {
		switch (res) {
			case -1:
				printf("Not enough memory\n");
				break;
			case -2:
				printf("Cannot read file %s\n", filename);
				break;
			case -3:
				printf("Cannot open file %s\n", filename);
				break;
			default:
				printf("Unknown error\n");
		}
		return -2;
	}
	t = (clock() - t) / CLOCKS_PER_SEC;
	printf("Successful reading (%.2lf sec)\n", t);

	tree.print_();

	printf("Searching every element now...\n");
	t = clock();
	res = tree.search(filename);
	t = (clock() - t) / CLOCKS_PER_SEC;
	if (!res) printf("Searching time: %.2lf sec\n", t);
	else switch(res) {
		case -1:
			printf("Cannot open file %s\n", filename);
			break;
		case -2:
			printf("Cannot read file %s\n", filename);
			break;
		default:
			printf("Unknown error\n");
	}

	printf("Deleting tree...\n");
	return 0;
}

