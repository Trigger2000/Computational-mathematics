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

vector matrix::solve_with_zeidel(const vector& f)
{
    matrix L = this->get_L();
    matrix D = this->get_D();
    matrix U = this->get_U();

    matrix temp = (L + D).get_reversed();
    matrix R = temp*(-1)*U;
    vector F = temp*f;

    double *x0 = new double[n_];
    for (int i = 0; i < n_; ++i)
    {
        x0[i] = 0;
    }
    vector u0{x0, n_};

    const double eps = 0.00001;
    vector diff = f - (*this)*u0;
    while (diff > eps)
    {
        u0 = R*u0 + F;
        diff = f - (*this)*u0;
    }
    
    return u0;
}

matrix matrix::get_reversed()
{
    matrix res{n_};

    for (int i = 0; i < n_; ++i)
    {
        double *f = new double[n_];

        for (int j = 0; j < n_; ++j)
        {
            if (i == j)
            {
                f[j] = 1;
            }
            else
            {
                f[j] = 0;
            }
        }

        vector res_g = this->solve_with_gauss(f);

        for (int j = 0; j < n_; ++j)
        {
            res.a_[j][i] = res_g.v_[j];
        }

        delete[] f;
    }

    return res;
}

matrix matrix::get_L()
{
    matrix res{n_};

    for (int i = 0; i < n_; ++i)
    {
        for (int j = 0; j < n_; ++j)
        {
            if (i > j)
            {
                res.a_[i][j] = a_[i][j];
            }
            else
            {
                res.a_[i][j] = 0;
            }
        }
    }

    return res;
}

matrix matrix::get_D()
{
    matrix res{n_};

    for (int i = 0; i < n_; ++i)
    {
        for (int j = 0; j < n_; ++j)
        {
            if (i == j)
            {
                res.a_[i][j] = a_[i][j];
            }
            else
            {
                res.a_[i][j] = 0;
            }
        }
    }

    return res;
}

matrix matrix::get_U()
{
    matrix res{n_};

    for (int i = 0; i < n_; ++i)
    {
        for (int j = 0; j < n_; ++j)
        {
            if (i < j)
            {
                res.a_[i][j] = a_[i][j];
            }
            else
            {
                res.a_[i][j] = 0;
            }
        }
    }

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

matrix operator*(const matrix& lhs, const int lambda)
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

std::ostream& operator<<(std::ostream& stream, const matrix& m)
{
    for (int i = 0; i < m.n_; ++i)
    {
        for (int j = 0; j < m.n_; ++j)
        {
            stream << m.a_[i][j] << ' ';
        }
        stream << '\n';
    }
    return stream;
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

vector matrix::find_lambdas()
{
    matrix cpy{a_, n_};

    for (int counter = 0; counter < 100; ++counter)
    {
        double max = 0.0;
        int i_max = 0, j_max = 0;
        for (int i = 0; i < n_; ++i)
        {
            for (int j = i + 1; j < n_; ++j)
            {
                if (std::abs(cpy.a_[i][j]) > max)
                {
                    max = std::abs(cpy.a_[i][j]);
                    i_max = i;
                    j_max = j;
                }
            }
        }
        if (i_max >= j_max)
        {
            break;
        }

        double phi = 0.5*std::atan(2*cpy.a_[i_max][j_max] / (cpy.a_[i_max][i_max] - cpy.a_[j_max][j_max]));

        double **u = new double*[n_];
        for (int i = 0; i < n_; ++i)
        {
            u[i] = new double[n_];
            for (int j = 0; j < n_; j++)
            {
                if (i == j)
                {
                    u[i][j] = 1;
                }
                else
                {
                    u[i][j] = 0;
                }
            }
        }
        u[i_max][i_max] = std::cos(phi);
        u[j_max][j_max] = std::cos(phi);
        u[i_max][j_max] = (-1)*std::sin(phi);
        u[j_max][i_max] = std::sin(phi);

        matrix um{u, n_};
        matrix umt = um.get_transported();
        cpy = umt*cpy*um;

        for (int i = 0; i < n_; ++i)
        {
            delete[] u[i];
        }
        delete[] u;
    }

    double *tmp = new double[n_];
    for (int i = 0; i < n_; ++i)
    {
        tmp[i] = cpy.a_[i][i];
    }
    vector res{tmp, n_};
    delete[] tmp;

    return res;
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

matrix matrix::get_transported()
{
    double **newarr = make_copy(a_, n_);
    for (int i = 0; i < n_; ++i)
    {
        for (int j = 0; j < n_; ++j)
        {
            newarr[i][j] = a_[j][i];
        }
    }

    matrix res{newarr, n_};
    for (int i = 0; i < n_; ++i)
    {
        delete[] newarr[i];
    }
    delete[] newarr;

    return res;
}

vector matrix::find_condition_numbers()
{
    vector res{3};
    matrix reversed = this->get_reversed();

    res.v_[0] = this->norm1()*reversed.norm1();
    res.v_[1] = this->norm2()*reversed.norm2();
    res.v_[2] = this->norm3()*reversed.norm3();

    return res;
}

double matrix::norm1()
{
    double res = 0.0;
    for (int i = 0; i < n_; ++i)
    {
        double sum = 0.0;
        for (int j = 0; j < n_; ++j)
        {
            sum += std::abs(a_[i][j]);
        }

        if (sum > res)
        {
            res = sum;
        }
    }
    return res;
}

double matrix::norm2()
{
    double res = 0.0;
    for (int i = 0; i < n_; ++i)
    {
        double sum = 0.0;
        for (int j = 0; j < n_; ++j)
        {
            sum += std::abs(a_[j][i]);
        }

        if (sum > res)
        {
            res = sum;
        }
    }

    return res;
}

double matrix::norm3()
{
    double res = 0.0;
    vector lambdas = this->find_lambdas();
    for (int i = 0; i < n_; ++i)
    {
        if (std::abs(lambdas.v_[i]) > res)
        {
            res = std::abs(lambdas.v_[i]);
        }
    }

    return res;
}