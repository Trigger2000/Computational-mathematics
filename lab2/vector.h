#include <iostream>
#include <unistd.h>
#include <cmath>

struct vector //geometrical vector
{
    vector() = delete;

    vector(int n);
    vector(double *v, int n);
    ~vector();

    vector& operator=(const vector& v);

    double *v_;
    int n_;
};

vector operator+(const vector& lhs, const vector& rhs);
vector operator-(const vector& lhs, const vector& rhs);
bool operator>(const vector& lhs, const double eps);
std::ostream& operator<<(std::ostream& stream, const vector& v);