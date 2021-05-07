#pragma once

#include <iostream>
#include <unistd.h>
#include <cmath>

struct vector //geometrical vector
{
    vector();
    vector(int n);
    vector(double *v, int n);
    ~vector();

    vector& operator=(const vector& v);

    double *v_ = nullptr;
    int n_ = 0;
};

vector operator+(const vector& lhs, const vector& rhs);
vector operator-(const vector& lhs, const vector& rhs);
vector operator*(const vector& lhs, const double lambda);