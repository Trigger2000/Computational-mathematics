#include <iostream>
#include <cmath>
#include <functional>
#include <string>

long double solve(std::string name, std::function<long double(long double)> func);

int main()
{
    solve("MPI", [](long double x){return std::sqrt(std::pow(0.5, x) + 1) + 1;});
    solve("MPI", [](long double x){return (-1) * std::log2((x - 1) * (x - 1) - 1);});
    solve("MPI", [](long double x){return x - (std::pow(0.5, x) + 1 - (x - 1) * (x - 1)) / 2;});
    solve("Newton", [](long double x){return x + (std::pow(0.5, x) + 1 - std::pow(x - 1, 2)) / 
                                                 (std::log(2) * std::pow(0.5, x) + 2 * (x - 1));});
    return 0;
}

long double solve(std::string name, std::function<long double(long double)> func)
{
    long double result = -1.0;
    for (int i = 0; i < 100; ++i)
    {
        long double prev = result;
        result = func(result);
        if (prev == result)
        {
            std::cout << name << " is converged towards " << result << " using " << i - 1 << " iterations\n";
            break;
        }
    }
    return result;
}