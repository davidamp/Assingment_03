This is a tools.h
#ifndef HEADER_FILE
#define HEADER_FILE
#include  <stdio.h>
#include  <math.h>
#include  <stdlib.h>

double **Metgen(int fil, int cold);
int JacobiMethod(int n, double **A, double *b, int *xi, double eps, int MaxIt);
double *Mat_Vec_Mult(int m, double **mot, double *arr);

#endif
