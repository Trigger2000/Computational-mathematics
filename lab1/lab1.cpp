#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <locale>
#include <iomanip>
#include <limits>

const long double real = 9.063077;
const long double x0 = 5.0;
const int upper_limit = 21;
long double f(long double x)
{
    return std::sin(x*x);
}

int main()
{
    auto formula1 = [](long double step){return (f(x0 + step) - f(x0)) / step; };
    auto formula2 = [](long double step){return (f(x0) - f(x0 - step)) / step; };
    auto formula3 = [](long double step){return (f(x0 + step) - f(x0 - step)) / (2*step); };

    auto formula4 = [](long double step){return 1.33 * (f(x0 + step) - f(x0 - step)) / (2*step) - 
                                                0.33 * (f(x0 + 2*step) - f(x0 - 2*step)) / (4*step); };

    auto formula5 = [](long double step){return 1.5 * (f(x0 + step) - f(x0 - step)) / (2*step) - 
                                                0.6 * (f(x0 + 2*step) - f(x0 - 2*step)) / (4*step) +
                                                0.1 * (f(x0 + 3*step) - f(x0 - 3*step)) / (6*step);};

    std::string file = "data.xls";
    std::ofstream fout(file);

    fout.imbue(std::locale("")); //set comma as a separator

    long double step = 1.0;
    for (int i = 1; i <= upper_limit; ++i)
    {
        fout << std::setprecision(std::numeric_limits<long double>::digits10 + 1) 
                     << step << '\t' << std::abs(real - formula1(step))
                     << '\t' << std::abs(real - formula2(step))
                     << '\t' << std::abs(real - formula3(step))
                     << '\t' << std::abs(real - formula4(step))
                     << '\t' << std::abs(real - formula5(step)) << '\n';
        step /= 2;
    }

    fout.close();

    return 0;
}