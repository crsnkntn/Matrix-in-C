#include "matrix.h"

Matrix* matrix_build (int m, int n) {
	Matrix *mat = (Matrix*)malloc(sizeof(Matrix));
    mat->m = m;
    mat->n = n;
    mat->entries = (double**)malloc(m * sizeof(double*));
    for (int i = 0; i < m; i++) {
        mat->entries[i] = (double*)malloc(n * sizeof(double*));
    }
    return mat;
}

Matrix* matrix_build_from_file (FILE* infile) {
    int m = 0, n = 0;
    fscanf(infile, "%d %d", &m, &n);
    Matrix* mat = matrix_build(m, n);
    int i = 0, j = 0;
    for (int k = 0; k < mat->m * mat->n; k++) {
        if (k != 0 && k % mat->n == 0) {
            i++;
            j = 0;
        }
        fscanf(infile, "%lf", &mat->entries[i][j]);
        j++;
    }
    return mat;
}

Matrix* matrix_copy (Matrix* other) {
    Matrix* copy = (Matrix*)malloc(sizeof(Matrix));
    copy->m = other->m;
    copy->n = other->n;
    copy->entries = (double**)malloc(other->m * sizeof(double*));
    for (int i = 0; i < other->m; i++) {
        copy->entries[i] = (double*)malloc(other->n * sizeof(double*));
    }
    for (int i = 0; i < copy->m; i++) {
        for (int j = 0; j < copy->n; j++) {
            copy->entries[i][j] = other->entries[i][j];
        }
    }
    return copy;
}

void matrix_fill (Matrix* a, FILE* in_file) {
    if (in_file == NULL) {
        return;
    }
    int i = 0, j = 0;
    for (int k = 0; k < a->m * a->n; k++) {
        if (k != 0 && k % a->n == 0) {
            i++;
            j = 0;
        }
        fscanf(in_file, "%lf", &a->entries[i][j]);
        j++;
    }
}

Matrix* matrix_add (Matrix* a, Matrix* b) {
    if (a->m != b->m || a->n != b->n) {
        return NULL;
    }
    Matrix *mat = matrix_build(a->m, a->n);
    for (int i = 0; i < a->m; i++) {
        for (int j = 0; j < a->n; j++) {
            mat->entries[i][j] = a->entries[i][j] + b->entries[i][j];
        }
    }
    return mat;
}

void matrix_add_constant (Matrix* a, double c) {
    for (int i = 0; i < a->m; i++) {
        for (int j = 0; j < a->n; i++) {
            a->entries[i][j] += c;
        }
    }
}

void matrix_sub_constant (Matrix* a, double c) {
    for (int i = 0; i < a->m; i++) {
        for (int j = 0; j < a->n; i++) {
            a->entries[i][j] -= c;
        }
    }
}

Matrix* matrix_subtract (Matrix* a, Matrix* b) {
    if (a->m != b->m || a->n != b->n) {
        return NULL;
    }
    Matrix *mat = matrix_build(a->m, a->n);
    for (int i = 0; i < a->m; i++) {
        for (int j = 0; j < a->n; j++) {
            mat->entries[i][j] = a->entries[i][j] - b->entries[i][j];
        }
    }
    return mat;
}

Matrix* matrix_transpose(Matrix* a) {
    Matrix* mat = matrix_build(a->n, a->m);
    for (int i = 0; i < a->n; i++) {
        for (int j = 0; j < a->m; j++) {
            mat->entries[i][j] = a->entries[j][i];
        }
    }
    return mat;
}

Matrix* matrix_dot (Matrix* a, Matrix* b) {
    if (a->m != b->n) {
        return NULL;
    }
    Matrix* mat = matrix_build(a->m, b->n);
    return mat;
}

void matrix_single_print (Matrix* a, FILE* outfile) {
    fprintf(outfile, "%dx%d\n", a->m, a->n);
    int g = 0;
    for (int i = 0; i < a->m; i++) {
        if (a->m > 10 && (i > 4 && i < a->m - 5)) {
            if (g == 0) {
                fprintf(outfile, "|");
                for (int j = 0; j < 13; j++) {
                    fprintf(outfile, "  .  ");
                }
                fprintf(outfile, " |\n");
            }
            g++;
        }
        else {
            fprintf(outfile, "| ");
            int k = 0;
            for (int j = 0; j < a->n; j++) {
                if (a->n > 10 && (j > 4 && j < a->n - 5)) {
                    if (k < 3) {
                        fprintf(outfile, "  .  ");
                    }
                    k++;
                }
                else {
                    fprintf(outfile, "%.2f ", a->entries[i][j]);
                }
            }
            fprintf(outfile, "|\n");
        }
    }
    fprintf(outfile, "\n");
}

void matrix_free (Matrix* mat) {
    for (int i = 0; i < mat->m; i++) {
        free(mat->entries[i]);
    }
    free(mat->entries);
    free(mat);
}
