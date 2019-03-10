#include "header.h"

double f(int, int);

int main(int argc, char ** argv) {
    char * name = 0;
    double res, t;
    double * a; // m x n
    int m, n;

    if (argc < 3 || argc > 4 || ((m = atoi(argv[1])) <= 0)
        || ((n = atoi(argv[2])) <= 0)) {
            printf("usage: %s m n [name_A]\n", argv[0]);
            return 1;
    }

    a = (double *)malloc(m * n * sizeof(double));
    if (!a) { printf("Not enough memory\n"); return 2; }

    if (argc == 4) name = argv[3];

    if (name) {
        int ret = read_matrix(name, a, m, n);
        if (ret < 0) {
            switch (ret) {
                case -1:
                    printf("Cannot open %s\n", name);
                    break;
                case -2:
                    printf("Cannot read %s\n", name);
                    break;
                default:
                    printf("Unknown error\n");
            }
            free(a);
            return 3;
        }
    } else init_matrix(a, m, n, f);
    
    print_matrix(a, m, n);
    t = clock();
    res = f1(a, m, n);
    t = (clock() - t) / CLOCKS_PER_SEC;
    // print_matrix(a, m, n);
    printf("Result: %lf\nTime: %.2lf\n", res, t);

    free(a);
    return 0;
}

double f1(double * a, int m, int n) {
    double max = 0, s;
    int i, j;

    for (j = 0; j < n; j++) max += fabs(a[j]);
    for (i = 1; i < m; i++) {
        s = 0;
        for (j = 0; j < n; j++) s += fabs(a[i * n + j]);
        if (s > max) max = s;
    }
    
    return max;
}


double f(int i, int j) {
    return fabs((double)(i - j));
}
