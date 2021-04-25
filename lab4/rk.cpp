#include "rk.h"

std::ostream& operator<<(std::ostream& stream, const std::vector<point> points)
{
    for (const auto& item: points)
    {
        stream.precision(5);
        stream << std::fixed;
        stream << item.t << "\t" << item.u << "\t" << item.x 
               << "\t" << item.y << "\t" << item.z << "\n";
    }

    return stream;
}

void initialize (std::vector<point>& points)
{
    points[0].t = 0;
    points[0].u = 1.73;
    points[0].x = 0.5;
    points[0].y = 0;
    points[0].z = 0;
}

std::vector<point> rk1 ()
{
    std::vector<point> result;
    result.reserve(static_cast<std::size_t>(20.0 / STEP) + 1);
    result.resize(static_cast<std::size_t>(20.0 / STEP) + 1);
    initialize(result);
    for (int i = 1; i <= static_cast<std::size_t>(20.0 / STEP); ++i)
    {
        double tk = result[i - 1].t;
        double uk = result[i - 1].u;
        double xk = result[i - 1].x;
        double yk = result[i - 1].y;
        double zk = result[i - 1].z;

        result[i].t = tk + STEP;
        result[i].x = xk + STEP * zk;
        result[i].y = yk + STEP * uk;
        result[i].z = zk - (STEP * xk) / (std::pow(xk*xk + yk*yk, 1.5));
        result[i].u = uk - (STEP * yk) / (std::pow(xk*xk + yk*yk, 1.5));
    }
    return result;
}

std::vector<point> rk2 ()
{
    std::vector<point> result;
    result.reserve(static_cast<std::size_t>(20.0 / STEP) + 1);
    result.resize(static_cast<std::size_t>(20.0 / STEP) + 1);
    initialize(result);
    for (int i = 1; i <= static_cast<std::size_t>(20.0 / STEP); ++i)
    {
        double tk = result[i - 1].t;
        double uk = result[i - 1].u;
        double xk = result[i - 1].x;
        double yk = result[i - 1].y;
        double zk = result[i - 1].z;

        double a2 = zk - (STEP * xk) / (2.0 * std::pow(xk*xk + yk*yk, 1.5));
        double b2 = uk - (STEP * yk) / (2.0 * std::pow(xk*xk + yk*yk, 1.5));
        double p = xk + (STEP * zk) / 2.0, q = yk + (STEP * uk) / 2.0;
        double c2 = (-1.0) * p / (std::pow(p*p + q*q, 1.5));
        double d2 = (-1.0) * q / (std::pow(p*p + q*q, 1.5));

        result[i].t = tk + STEP;
        result[i].x = xk + STEP * a2;
        result[i].y = yk + STEP * b2;
        result[i].z = zk + STEP * c2;
        result[i].u = uk + STEP * d2;
    }
    return result;
}

std::vector<point> rk3 ()
{
    std::vector<point> result;
    result.reserve(static_cast<std::size_t>(20.0 / STEP) + 1);
    result.resize(static_cast<std::size_t>(20.0 / STEP) + 1);
    initialize(result);
    for (int i = 1; i <= static_cast<std::size_t>(20.0 / STEP); ++i)
    {
        double tk = result[i - 1].t;
        double uk = result[i - 1].u;
        double xk = result[i - 1].x;
        double yk = result[i - 1].y;
        double zk = result[i - 1].z;
        
        double a1 = zk;
        double b1 = uk;
        double c1 = ((-1.0) * xk) / (std::pow(xk*xk + yk*yk, 1.5));
        double d1 = ((-1.0) * yk) / (std::pow(xk*xk + yk*yk, 1.5));

        double a2 = zk + STEP * c1 / 2.0;
        double b2 = uk + STEP * d1 / 2.0;
        double p = xk + (STEP * a1) / 2.0, q = yk + (STEP * b1) / 2.0;
        double c2 = (-1.0) * p / (std::pow(p*p + q*q, 1.5));
        double d2 = (-1.0) * q / (std::pow(p*p + q*q, 1.5));

        double a3 = zk + STEP * c2;
        double b3 = uk + STEP * d2;
        double p1 = xk + STEP * a2;
        double q1 = yk + STEP * b2;
        double c3 = (-1.0) * p1 / (std::pow(p1*p1 + q1*q1, 1.5));
        double d3 = (-1.0) * q1 / (std::pow(p1*p1 + q1*q1, 1.5));

        result[i].t = tk + STEP;
        result[i].x = result[i - 1].x + STEP * (a1 + 4.0 * a2 + a3) / 6.0;
        result[i].y = result[i - 1].y + STEP * (b1 + 4.0 * b2 + b3) / 6.0;
        result[i].z = result[i - 1].z + STEP * (c1 + 4.0 * c2 + c3) / 6.0;
        result[i].u = result[i - 1].u + STEP * (d1 + 4.0 * d2 + d3) / 6.0;
    }
    return result;
}

std::vector<point> rk4 ()
{
    std::vector<point> result;
    result.reserve(static_cast<std::size_t>(20.0 / STEP) + 1);
    result.resize(static_cast<std::size_t>(20.0 / STEP) + 1);
    initialize(result);
    for (int i = 1; i <= static_cast<std::size_t>(20.0 / STEP); ++i)
    {
        double tk = result[i - 1].t;
        double uk = result[i - 1].u;
        double xk = result[i - 1].x;
        double yk = result[i - 1].y;
        double zk = result[i - 1].z;
        
        double a1 = zk;
        double b1 = uk;
        double c1 = ((-1.0) * xk) / (std::pow(xk*xk + yk*yk, 1.5));
        double d1 = ((-1.0) * yk) / (std::pow(xk*xk + yk*yk, 1.5));

        double a2 = zk + STEP * c1 / 2.0;
        double b2 = uk + STEP * d1 / 2.0;
        double p = xk + (STEP * a1) / 2.0, q = yk + (STEP * b1) / 2.0;
        double c2 = (-1.0) * p / (std::pow(p*p + q*q, 1.5));
        double d2 = (-1.0) * q / (std::pow(p*p + q*q, 1.5));

        double a3 = zk + STEP * c2 / 2.0;
        double b3 = uk + STEP * d2 / 2.0;
        double p1 = xk + STEP * a2 / 2.0;
        double q1 = yk + STEP * b2 / 2.0;
        double c3 = (-1.0) * p1 / (std::pow(p1*p1 + q1*q1, 1.5));
        double d3 = (-1.0) * q1 / (std::pow(p1*p1 + q1*q1, 1.5));

        double a4 = zk + STEP * c3;
        double b4 = uk + STEP * d3;
        double p2 = xk + STEP * a3;
        double q2 = yk + STEP * b3;
        double c4 = (-1.0) * p2 / (std::pow(p2*p2 + q2*q2, 1.5));
        double d4 = (-1.0) * q2 / (std::pow(p2*p2 + q2*q2, 1.5));

        result[i].t = tk + STEP;
        result[i].x = result[i - 1].x + STEP * (a1 + 2.0 * a2 + 2.0 * a3 + a4) / 6.0;
        result[i].y = result[i - 1].y + STEP * (b1 + 2.0 * b2 + 2.0 * b3 + b4) / 6.0;
        result[i].z = result[i - 1].z + STEP * (c1 + 2.0 * c2 + 2.0 * c3 + c4) / 6.0;
        result[i].u = result[i - 1].u + STEP * (d1 + 2.0 * d2 + 2.0 * d3 + d4) / 6.0;
    }
    return result;
}