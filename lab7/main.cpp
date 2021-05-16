#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <functional>

#define STEP 0.001

struct point
{
    double x = 0.0;
    double y = 0.0;
    double y1 = 0.0;
};

std::vector<point> solve(double b, std::function<double(double)> func);
std::vector<point> solve_with_rk3(double alpha, std::function<double(double)> func);

std::ostream& operator<<(std::ostream& stream, const std::vector<point>& points);

int main()
{
    /* std::vector<point> result1 = solve(0.5, [](double x){return std::exp(x);});
    std::vector<point> result2 = solve(1.0, [](double x){return std::exp(x);});
    std::vector<point> result3 = solve(1.4, [](double x){return std::exp(x);}); */

    std::vector<point> result1 = solve(0.5, [](double x){return (-1.0) * std::exp(x);});
    std::vector<point> result2 = solve(1.0, [](double x){return (-1.0) * std::exp(x);});
    std::vector<point> result3 = solve(1.4, [](double x){return (-1.0) * std::exp(x);});

    std::ofstream file1("data1.dat");
    std::ofstream file2("data2.dat");
    std::ofstream file3("data3.dat");

    file1 << result1;
    file2 << result2;
    file3 << result3;

    return 0;
}

std::vector<point> solve_with_rk3(double alpha, std::function<double(double)> func)
{
    std::vector<point> result;
    result.reserve(static_cast<std::size_t>(1.0 / STEP) + 1);
    result.resize(static_cast<std::size_t>(1.0 / STEP) + 1);
    result[0].x = 0;
    result[0].y = 1;
    result[0].y1 = alpha;

    for (int i = 1; i <= static_cast<std::size_t>(1.0 / STEP); ++i)
    {
        double xk = result[i - 1].x;
        double yk = result[i - 1].y;
        double y1k = result[i - 1].y1;
        
        double k1 = y1k;
        double m1 = func(yk);

        double k2 = y1k + (STEP * m1) / 3.0;
        double m2 = func(yk + (STEP * k1) / 3.0);

        double k3 = y1k + (2.0 * STEP * m2);
        double m3 = func(yk + (2.0 * STEP * k2) / 3.0);

        result[i].x = xk + STEP;
        result[i].y = yk + STEP * (k1 + 3.0 * k3) / 4.0;
        result[i].y1 = y1k + STEP * (m1 + 3.0 * m3) / 4.0;
    }
    return result;
}

std::vector<point> solve(double b, std::function<double(double)> func)
{
    double alpha = -5.0;
    double h = 0.001;
    std::vector<point> result = solve_with_rk3(alpha, func);
    while (std::abs(result.back().y - b) >= 0.01)
    {
        std::vector<point> helper = solve_with_rk3(alpha + h, func);
        alpha -= h * (result.back().y - b) / (helper.back().y - result.back().y);
        result = solve_with_rk3(alpha, func);
    }

    return result;
}

std::ostream& operator<<(std::ostream& stream, const std::vector<point>& points)
{
    for (const auto& item: points)
    {
        stream.precision(5);
        stream << std::fixed;
        stream << item.x << '\t' << item.y << '\n';
    }

    return stream;
}