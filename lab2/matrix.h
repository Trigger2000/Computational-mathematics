#include "vector.h"

struct matrix // square matrix with all non zero elements
{
    matrix() = delete;

    matrix(int n);
    matrix(double **a, int n);
    ~matrix();

    vector solve_with_gauss(double *f); // without checks! transform input matrix!
    vector solve_with_zeidel(const vector& f); // without checks!
    vector find_lambdas(); // uses rotation method, suitable only for symmetrical matrices!
    vector find_condition_numbers(); // condition numbers with respect to 1, 2 and 3 norms

    matrix& operator=(const matrix& m);

    matrix get_reversed();
    matrix get_transported();
    matrix get_L();
    matrix get_D();
    matrix get_U();
    double norm1();
    double norm2();
    double norm3();

    double **a_;
    int n_;
};

vector operator*(const matrix& lhs, const vector& rhs);
matrix operator*(const matrix& lhs, const matrix& rhs);
matrix operator*(const matrix& lhs, const int lambda);
matrix operator+(const matrix& lhs, const matrix& rhs);
std::ostream& operator<<(std::ostream& stream, const matrix& m);

double** make_copy(double **input, int size);