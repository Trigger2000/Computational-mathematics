#include "matrix.h"

matrix::matrix(double **a, int n)
{
    n_ = n;
    a_ = make_copy(a, n);
}

matrix::matrix(int n)
{
    n_ = n;
    a_ = new double*[n];
    for (int i = 0; i < n; ++i)
    {
        a_[i] = new double[n];
        for (int j = 0; j < n; ++j)
        {
            a_[i][j] = 0;
        }
    }
}

matrix::~matrix()
{
    for (int i = 0; i < n_; ++i)
    {
        delete[] a_[i];
    }

    delete[] a_;
}

vector matrix::solve_with_gauss(double *f) 
{
    double **temp = make_copy(a_, n_);
    double *x = new double[n_];

    for (int k = 1; k < n_; ++k)
    {
        for (int j = k; j < n_; ++j)
        {
            double m = temp[j][k-1] / temp[k-1][k-1];
            for (int i = 0; i < n_; ++i)
            {
                temp[j][i] = temp[j][i] - m*temp[k-1][i];
            }
            f[j] = f[j] - m*f[k-1];
        }
    }

    for (int i = n_ - 1; i >= 0; --i)
    {
        x[i] = f[i] / temp[i][i];
        for (int c = n_ - 1; c > i; --c)
        {
            x[i] = x[i] - temp[i][c]*x[c]/temp[i][i];
        } 
    }

    for (int i = 0; i < n_; ++i)
    {
        delete[] temp[i];
    }
    delete[] temp;

    vector res{x, n_};
    delete[] x;
    return res;
}

matrix operator*(const matrix& lhs, const matrix& rhs)
{
    matrix res{lhs.n_};
    for (int i = 0; i < lhs.n_; ++i)
    {
        for (int j = 0; j < lhs.n_; ++j)
        {
            double s = 0;
            for (int k = 0; k < lhs.n_; ++k)
            {
                s += lhs.a_[i][k]*rhs.a_[k][j];
            }
            res.a_[i][j] = s;
        }
    }

    return res;
}

matrix operator*(const matrix& lhs, const double lambda)
{
    matrix res{lhs.a_, lhs.n_};

    for (int i = 0; i < lhs.n_; ++i)
    {
        for (int j = 0; j < lhs.n_; ++j)
        {
            res.a_[i][j] *= lambda;
        }
    }

    return res;
}

matrix operator+(const matrix& lhs, const matrix& rhs)
{
    matrix res{lhs.n_};
    for (int i = 0; i < lhs.n_; ++i)
    {
        for (int j = 0; j < lhs.n_; ++j)
        {
            res.a_[i][j] = lhs.a_[i][j] + rhs.a_[i][j];
        }
    }

    return res;
}

vector operator*(const matrix& lhs, const vector& rhs)
{
    vector res{rhs.n_};
    for (int i = 0; i < rhs.n_; ++i)
    {
        for (int j = 0; j < rhs.n_; ++j)
        {
            res.v_[i] += lhs.a_[i][j]*rhs.v_[j];
        }
    }

    return res;
}

matrix& matrix::operator=(const matrix& m)
{
    if (&m == this)
        return *this;

    for (int i = 0; i < n_; ++i)
    {
        delete[] a_[i];
    }
    delete[] a_;
    
    n_ = m.n_;
    a_ = make_copy(m.a_, m.n_);

    return *this;
}

double** make_copy(double **input, int size)
{
    double **res = new double*[size];
    for (int i = 0; i < size; ++i)
    {
        res[i] = new double[size];
        for (int j = 0; j < size; ++j)
        {
            res[i][j] = input[i][j];
        }
    }
    return res;
}

void matrix::make_unitary()
{
    for (int i = 0; i < n_; ++i)
    {
        for (int j = 0; j < n_; ++j)
        {
            a_[i][j] = 0;
        }
    }

    for (int i = 0; i < n_; ++i)
    {
        a_[i][i] = 1;
    }
}