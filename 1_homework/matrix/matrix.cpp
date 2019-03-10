#include "header.h"

#define MAX_PRINT 10
#define WITHPOINT 0
#define SIZE 32

// -------------------------------------------------------------

void bad_transpose(double * a, int n) {
	int i = 0, j = 0, x = 0;
	for (; i < n; i++) {
		for (j = 0; j < i; j++) {
			x = a[i * n + j];
			a[i * n + j] = a[j * n + i];
			a[j * n + i] = x;
		}
	}
}

void block_transpose(double * a, int n) {
	if (n % SIZE) {
		printf("this works only for n mod SIZE == 0\n");
		return;
	}
	double buf1[SIZE * SIZE];
	double buf2[SIZE * SIZE];
	int i = 0, j = 0;
	for (i = 0; i < n; i += SIZE) {
		for (int t = 0; t < SIZE; t++) {
			for (int k = 0; k < t; k++) {
				j = a[(i + t) * n + i + k];
				a[(i + t) * n + i + k] = a[(i + k) * n + i + t];
				a[(i + k) * n + i + t] = j;
			}
		}
		for (j = 0; j < i; j += SIZE) {
			for (int t = 0; t < SIZE; t++) {
				for (int k = 0; k < SIZE; k++) {
					buf1[t * SIZE + k] = a[(i + t) * n + j + k];
					buf2[t * SIZE + k] = a[(j + t) * n + i + k];
				}
			}
			for (int t = 0; t < SIZE; t++) {
				for (int k = 0; k < SIZE; k++) {
					a[(i + t) * n + j + k] = buf2[k * SIZE + t];
					a[(j + t) * n + i + k] = buf1[k * SIZE + t];
				}
			}
		}
	}
}

// m x n
void o_transpose(double * a, double * b, int m, int n, int offset) {
	static int N = n;
	static double * aa = a;
	static double * bb = b;
	if (n == 1 && m == 1) return;
//	printf("#\n"); print_matrix(a, m, n);
	if (n > 1) {
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n/2; j++) {
				b[i * n/2 + j] = a[i * (n + offset) + j];
				b[(i + m) * n/2 + j] = a[i * (n + offset) + j + n/2];
			}
		}
//	printf("a:\n");print_matrix(a, 2*N, N/2);
//	printf("b:\n");print_matrix(b, 2*N, N/2);
		o_transpose(b, a, m/2, n/2, offset);
		o_transpose(b + m*n/4, a, m/2, n/2, offset);
		o_transpose(b + m*n/2, a, m/2, n/2, offset);
		o_transpose(b + 3*m*n/4, a, m/2, n/2, offset);
//	printf("@\n");print_matrix(a + m * n/2, m, n/2);
		
//	printf("@\n"); print_matrix(b, m, n);
		for (int i = 0; i < m/2; i++) {
			for (int j = 0; j < n/2; j++) {
				a[i * n + j] = b[i * n/2 + j];
				a[i * n + j + n/2] = b[(i + n/2) * n/2 + j];
				a[(i + n/2) * n + j] = b[(i + n) * n/2 + j];
				a[(i + n/2) * n + j + n/2] = b[(i + 3*n/2) * n/2 + j];
			}
		}
//	printf("!\n"); print_matrix(a, m, n);
	} else { return;
		for (int i = 0; i < m/2; i++) {
			for (int j = 0; j < n; j++) {
				b[i * 2*n + j] = a[i * (n + offset) + j];
				b[i * 2*n + j + n] = a[(i + m/2) * (n + offset) + j];
			}
		}
//		print_matrix(b, m, n);
//	printf("a:\n");print_matrix(b, N);
//	printf("b:\n");print_matrix(b, N);
		o_transpose(a, b, m/2, n, offset + n/2);
	printf("@\n");print_matrix(a + m * n/2, m, n/2);
		o_transpose(a + m * n/2, b + m * n/2, m/2, n, offset + n/2);
	printf("@\n");print_matrix(a + m * n/2, m, n/2);
	}
}

// -------------------------------------------------------------

int read_matrix(double * a, int n, const char * name) {
    FILE * fp = 0;
    int i = 0;
	int j = 0;

    if (!(fp = fopen(name, "r"))) return -1;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (fscanf(fp, "%lf", a + i * n + j) != 1) {
                fclose(fp);
                return -2;
            }
        }
    }

    fclose(fp);
    return 0;
}

void print_matrix(double * a, int m, int n) {
    int i = 0;
	int j = 0;
	int nn = n;
//    n = (n > MAX_PRINT) ? MAX_PRINT : n;
//    m = (m > MAX_PRINT) ? MAX_PRINT : m;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if (WITHPOINT) printf(" %lf", a[i * nn + j]);
            else printf(" %.lf", a[i * nn + j]);
        }
        printf("\n");
    }
    for (i = 0; i <= n; i++) printf("- ");
    printf("\n");
}
void print_matrix(double * a, int n) {
    int i = 0;
	int j = 0;
	int nn = n;
    n = (n > MAX_PRINT) ? MAX_PRINT : n;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (WITHPOINT) printf(" %lf", a[i * nn + j]);
            else printf(" %.lf", a[i * nn + j]);
        }
        printf("\n");
    }
    for (i = 0; i <= n; i++) printf("- ");
    printf("\n");
}

void init_matrix(double * a, int n, double (*f)(int, int)) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            a[i * n + j] = f(i, j);
        }
    }
}

void sum(double * a, double * b, int n) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			a[i * n + j] += b[i * n + j];
}

int symmetric(double * a, int n) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < i; j++)
			if (a[i * n + j] != a[j * n + i]) return 0;
	return 1;
}


