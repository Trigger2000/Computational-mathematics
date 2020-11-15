#include <iostream>
#include <cmath>
#include <functional>

long double solve_with_MPI(std::function<long double(long double)> func);
long double solve_with_Newton();

int main()
{
    solve_with_MPI([](long double x){return std::sqrt(std::pow(0.5, x) + 1) + 1;});
    solve_with_MPI([](long double x){return (-1) * std::log2((x - 1) * (x - 1) - 1);});
    solve_with_MPI([](long double x){return x - (std::pow(0.5, x) + 1 - (x - 1) * (x - 1)) / 2;});
    solve_with_Newton();
    return 0;
}

long double solve_with_MPI(std::function<long double(long double)> func)
{
    long double result = -5.0;
    for (int i = 0; i < 100; ++i)
    {
        long double prev = result;
        result = func(result);
        if (prev == result)
        {
            std::cout << "MPI is converged towards " << result << " using " << i - 1 << " iterations\n";
            break;
        }
    }
    return result;
}

long double solve_with_Newton()
{
    long double result = 0.0;
    for (int i = 0; i < 10; ++i)
    {
        long double prev = result;
        result = result + (std::pow(0.5, result) + 1 - std::pow(result - 1, 2)) / 
                          (std::log(2) * std::pow(0.5, result) + 2 * (result - 1));
        if (prev == result)
        {
            std::cout << "Newton is converged towards " << result << " using " << i - 1 << " iterations\n";
            break;
        }
    }
    return result;
}