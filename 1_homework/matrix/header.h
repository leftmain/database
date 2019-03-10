#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// io
int read_matrix(double *, int, const char *);
void print_matrix(double *, int);
void print_matrix(double *, int, int);
void init_matrix(double *, int, double (*)(int, int));

void sum(double *, double *, int);
int symmetric(double *, int);

// bad algorithm
void bad_transpose(double *, int);

// cache-blocked
void block_transpose(double *, int);

// cache-oblivios
void o_transpose(double *, double *, int, int, int = 0);

#endif

