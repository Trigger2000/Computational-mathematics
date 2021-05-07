#pragma once

#include "vector.h"

struct matrix // square matrix with all non zero elements
{
    matrix() = delete;

    matrix(int n);
    matrix(double **a, int n);
    ~matrix();

    vector solve_with_gauss(double *f); // without checks! transform input matrix!
    void make_unitary();

    matrix& operator=(const matrix& m);

    double **a_;
    int n_;
};

vector operator*(const matrix& lhs, const vector& rhs);
matrix operator*(const matrix& lhs, const matrix& rhs);
matrix operator*(const matrix& lhs, const double lambda);
matrix operator+(const matrix& lhs, const matrix& rhs);

double** make_copy(double **input, int size);