#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    double** entries;
    int m;
    int n;
} Matrix;

// Matrix Functions
Matrix* matrix_build (int m, int n);
Matrix* matrix_build_from_file (FILE* infile);
Matrix* matrix_copy (Matrix* m);
Matrix* matrix_dot (Matrix* a, Matrix* b);
Matrix* matrix_cross (Matrix* a, Matrix* b);
Matrix* matrix_add (Matrix* a, Matrix* b);
void matrix_add_constant (Matrix* a, double c);
void matrix_sub_constant (Matrix* a, double c);
Matrix* matrix_subtract (Matrix* a, Matrix* b);
Matrix* matrix_transpose (Matrix* a);
void matrix_single_print(Matrix* a, FILE* outfile);
void matrix_free (Matrix* m);
