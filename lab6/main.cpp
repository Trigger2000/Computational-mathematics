#include <iostream>
#include <cmath>
#include <fstream>

#define STEP 0.1

double* calculate_model_equation();
double* calculate_equation();

int main()
{
    double *model_solution = calculate_model_equation();
    double *task_solution = calculate_equation();
    std::ofstream file1("data1.dat");
    std::ofstream file2("data2.dat");
    for (int i = 0; i <= 10; ++i)
    {
        file1 << i * STEP << '\t' << model_solution[i] << '\n';
        file2 << i * STEP << '\t' << task_solution[i] << '\n';
    }

    return 0;
}

double* calculate_model_equation()
{
    double sqrt_e = 1.65;
    double an = sqrt_e;
    double cn = sqrt_e;
    double bn = an + cn + STEP * STEP * sqrt_e;
    double dn = (-1.0) * STEP * STEP * std::cos(0.5);
    double b0 = sqrt_e / STEP + 1.0;
    double c0 = sqrt_e / STEP;
    double d0 = -1.0;

    double bN = (-1.0) * sqrt_e / STEP - 1.0;
    double aN = sqrt_e / STEP;
    double dN = 0.0;

    double *cof_p = new double[12];
    double *cof_q = new double[12];
    cof_p[1] = c0 / b0;
    cof_q[1] = (-1.0) * d0 / b0;

    for (int i = 2; i <= 10; ++i)
    {
        cof_p[i] = cn / (bn - an * cof_p[i - 1]);
        cof_q[i] = (an * cof_q[i - 1] - dn) / (bn - an * cof_p[i - 1]);
    }

    double *solution = new double[11];
    solution[10] = (aN * cof_q[10] - dN) / (bN - aN * cof_p[10]);

    for (int i = 9; i >= 0; --i)
    {
        solution[i] = cof_p[i + 1] * solution[i + 1] + cof_q[i + 1]; 
    }

    return solution;
}

double* calculate_equation()
{
    double b0 = 1.0 / STEP + 1.0;
    double c0 = 1.0 / STEP;
    double d0 = -1.0;
    double bN = (-2.71) / STEP - 1.0;
    double aN = 2.71 / STEP;
    double dN = 0.0;

    double *cof_p = new double[12];
    double *cof_q = new double[12];
    cof_p[1] = c0 / b0;
    cof_q[1] = (-1.0) * d0 / b0;

    for (int i = 2; i <= 10; ++i)
    {
        double xn = STEP * (i - 1);
        double an = std::exp(xn - 0.5 * STEP);
        double cn = std::exp(xn + 0.5 * STEP);
        double bn = an + cn + STEP * STEP * std::exp(xn);
        double dn = (-1.0) * STEP * STEP * std::cos(xn);
        cof_p[i] = cn / (bn - an * cof_p[i - 1]);
        cof_q[i] = (an * cof_q[i - 1] - dn) / (bn - an * cof_p[i - 1]);
    }

    double *solution = new double[11];
    solution[10] = (aN * cof_q[10] - dN) / (bN - aN * cof_p[10]);

    for (int i = 9; i >= 0; --i)
    {
        solution[i] = cof_p[i + 1] * solution[i + 1] + cof_q[i + 1]; 
    }

    return solution;
}