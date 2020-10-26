#include "vector.h"

vector::vector(int n)
{
    n_ = n;
    v_ = new double[n];
    for (int i = 0; i < n; ++i)
    {
        v_[i] = 0;
    }
}

vector::vector(double *v, int n)
{
    n_ = n;
    v_ = new double[n];

    for (int i = 0; i < n; ++i)
    {
        v_[i] = v[i];
    }
}

vector::~vector()
{
    delete[] v_;
}

vector operator+(const vector& lhs, const vector& rhs)
{
    vector res{lhs.v_, lhs.n_};
    for (int i = 0; i < lhs.n_; ++i)
    {
        res.v_[i] += rhs.v_[i];
    }

    return res;
}

vector operator-(const vector& lhs, const vector& rhs)
{
    vector res{lhs.v_, lhs.n_};
    for (int i = 0; i < lhs.n_; ++i)
    {
        res.v_[i] -= rhs.v_[i];
    }

    return res;
}

std::ostream& operator<<(std::ostream& stream, const vector& v)
{
    for (int i = 0; i < v.n_; ++i)
    {
        stream << v.v_[i] << ' ';
    }
    stream << '\n';
    return stream;
}

bool operator>(const vector& lhs, const double eps)
{
    double max = 0;
    for (int i = 0; i < lhs.n_; ++i)
    {
        if (std::abs(lhs.v_[i]) > max)
        {
            max = std::abs(lhs.v_[i]);
        }
    }

    if (max <= eps)
        return false;

    return true;
}

vector& vector::operator=(const vector& v)
{
    if (&v == this)
        return *this;

    n_ = v.n_;
    delete[] v_;
    v_ = new double[n_];

    for (int i = 0; i < n_; ++i)
    {
        v_[i] = v.v_[i];
    }

    return *this;
}