#include "matrix.h"

int main() 
{
    double **a = new double*[10];
    double *f = new double[10];
    for (int i = 0; i < 10; ++i)
    {
        a[i] = new double[10];
        for (int j = 0; j < 10; ++j)
        {
            if (i == j)
            {
                a[i][j] = 1;
            }
            else
            {
                a[i][j] = 1.0/(i + j + 2);
            }
        }
        f[i] = 1.0/(i + 1);
    }

    matrix m{a, 10};
    vector vf{f, 10};

    vector gauss_sol = m.solve_with_gauss(f);
    std::cout << "gauss solution\n" << gauss_sol << '\n';

    std::cout << "residual for gauss\n" << vf-m*gauss_sol << '\n'; 

    vector zeidel_sol = m.solve_with_zeidel(vf);
    std::cout << "zeidel solution\n" << zeidel_sol << '\n';

    std::cout << "residual for zeidel\n" << vf-m*zeidel_sol << '\n';

    vector lambdas = m.find_lambdas();
    std::cout << "lambdas\n" << lambdas << '\n';

    vector condition_numbers = m.find_condition_numbers();
    std::cout << "condition numbers\n" << condition_numbers << '\n';

    for (int i = 0; i < 10; ++i)
    {
        delete[] a[i];
    }
    delete[] a;
    delete[] f;

    return 0;
}