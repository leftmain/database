#include "header.h"

int check(double *, double *, int, const char *);
double f(int, int);
double f(int i, int j) {
	return (double)(abs(2*i + j) % 10);
}

int main(int argc, char ** argv) {
	double * a = 0;
	double * b = 0;
	int n = 13;
	int res = 0;
	double t1 = 0;
	double t2 = 0;
	double t3 = 0;
	const char * file = 0;

	if (argc < 1 || argc > 3 || argc > 1 && (n = atoi(argv[1])) <= 0) {
		printf("usage: %s [n] [filename]\n", argv[0]);
		return -1;
	}
	if (argc == 3) file = argv[2];
	n = pow(2, n);
	printf("n = %d\n", n);

	a = (double *)malloc(n * n * sizeof(double));
	if (!a) {
		printf("Not enough memory\n");
		return -2;
	}
	b = (double *)malloc(n * n * sizeof(double));
	if (!b) {
		free(a);
		printf("Not enough memory\n");
		return -2;
	}

	if (file) {
		if ((res = read_matrix(a, n, file)) < 0) {
			switch(res) {
				case -1:
					printf("Cannot open %s\n", file);
					break;
				case -2:
					printf("Cannot read %s\n", file);
					break;
				default:
					printf("Unknown error\n");
			}
			free(a);
			free(b);
			return -3;
		}
	} else init_matrix(a, n, f);


	print_matrix(a, n);
	t1 = clock();
	bad_transpose(a, n);
	t1 = (clock() - t1) / CLOCKS_PER_SEC;
	printf("Bad time: %.2lf\n", t1);
	print_matrix(a, n);
	if (check(a, b, n, file)) {
		free(a);
		free(b);
		return 0;
	}

	printf("Now cache-blocked algorithm\n");

	t2 = clock();
	block_transpose(a, n);
	t2 = (clock() - t2) / CLOCKS_PER_SEC;
	print_matrix(a, n);
	printf("Block time: %.2lf\n", t2);
	if (check(a, b, n, file)) {
		free(a);
		free(b);
		return 0;
	}

	printf("Block %.2lf times faster than usual\n", t1 / t2);
	printf("Now cache-oblivious algorithm\n");

	t3 = clock();
	o_transpose(a, b, n, n);
	t3 = (clock() - t3) / CLOCKS_PER_SEC;
	print_matrix(a, n);
	printf("Cache-oblivious time: %.2lf\n", t3);

	printf("Cache-oblivious %.2lf times faster than usual\n", t1/t3);
	
	if (check(a, b, n, file)) {
		free(a);
		free(b);
		return 0;
	}

	free(a);
	free(b);
	return 0;
}

int check(double * a, double * b, int n, const char * file) {
	static int count = 1;
	int res = 0;
	count = (count == 1) ? 0 : 1;
	if (file) {
		printf("Checking now\nReading original file..\n");
		if ((res = read_matrix(b, n, file)) < 0) {
			switch(res) {
				case -1:
					printf("Cannot open %s\n", file);
					break;
				case -2:
					printf("Cannot read %s\n", file);
					break;
				default:
					printf("Unknown error\n");
			}
			return 1;
		}
		printf("Comparing..\n");
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (count) {
					if (a[i * n + j] != b[i * n + j]) {
						printf("Error\n");
						free(a); free(b);
						return 0;
					}
				} else {
					if (a[i * n + j] != b[j * n + i]) {
						printf("Error\n");
						free(a); free(b);
						return 0;
					}
				}
			}
		}
		printf("Ok\n");
	} else {
		printf("Checking..\n");
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (count) {
					if (a[i * n + j] != f(i, j)) {
						printf("Error\n");
						return 1;
					}
				} else {
					if (a[i * n + j] != f(j, i)) {
						printf("Error\n");
						return 1;
					}
				}
			}
		}
		printf("Ok\n");
	}
	return 0;
}


