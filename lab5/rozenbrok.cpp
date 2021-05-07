#include "rozenbrok.h"

std::vector<vector> calculate_plain()
{
    std::vector<vector> res(static_cast<size_t>(Tk / STEP));
    res[0].v_ = new double[4];
    res[0].n_ = 4;
    res[0].v_[0] = x0_s;
    res[0].v_[1] = y0_s;
    res[0].v_[2] = a10_s;
    res[0].v_[3] = a20_s;

    for (int i = 1; i < static_cast<size_t>(Tk / STEP); ++i)
    {
        res[i].v_ = new double[4];
        res[i].n_ = 4;
        // calculating right side
        vector func_u_n{4};
        double xn = res[i - 1].v_[0];
        double yn = res[i - 1].v_[1];
        double a1n = res[i - 1].v_[2];
        double a2n = res[i - 1].v_[3];
        func_u_n.v_[0] = xn * (2.0 * a1n - 0.5 * xn - (a1n * a1n) / (a2n * a2n) * yn);
        func_u_n.v_[1] = yn * (2.0 * a2n - 0.5 * yn - (a2n * a2n) / (a1n * a1n) * xn);
        func_u_n.v_[2] = epsilon_s * (2.0 - 2.0 * a1n / (a2n * a2n) * yn);
        func_u_n.v_[3] = epsilon_s * (2.0 - 2.0 * a2n / (a1n * a1n) * xn);
        vector func_arg = res[i - 1] + func_u_n * STEP * (-0.577);

        double xn_arg = func_arg.v_[0];
        double yn_arg = func_arg.v_[1];
        double a1n_arg = func_arg.v_[2];
        double a2n_arg = func_arg.v_[3];
        vector f{4};
        f.v_[0] = xn_arg * (2.0 * a1n_arg - 0.5 * xn_arg - (a1n_arg * a1n_arg) / (a2n_arg * a2n_arg) * yn_arg);
        f.v_[1] = yn_arg * (2.0 * a2n_arg - 0.5 * yn_arg - (a2n_arg * a2n_arg) / (a1n_arg * a1n_arg) * xn_arg);
        f.v_[2] = epsilon_s * (2.0 - 2.0 * a1n_arg / (a2n_arg * a2n_arg) * yn_arg);
        f.v_[3] = epsilon_s * (2.0 - 2.0 * a2n_arg / (a1n_arg * a1n_arg) * xn_arg);

        // calculating equation matrix
        matrix B{4};
        B.a_[0][0] = 2.0 * a1n - xn - (a1n * a1n) / (a2n * a2n) * yn;
        B.a_[0][1] = ((-1.0) * a1n * a1n * xn) / (a2n * a2n);
        B.a_[0][2] = xn * 2.0 * (1.0 - (a1n * yn) / (a2n * a2n));
        B.a_[0][3] = 2.0 * xn * yn * a1n * a1n / (std::pow(a2n, 3.0));

        B.a_[1][0] = ((-1.0) * a2n * a2n * yn) / (a1n * a1n);
        B.a_[1][1] = 2.0 * a2n - yn - (a2n * a2n) / (a1n * a1n) * xn;
        B.a_[1][2] = 2.0 * xn * yn * a2n * a2n / (std::pow(a1n, 3.0));
        B.a_[1][3] = yn * 2.0 * (1.0 - (a2n * xn) / (a1n * a1n));

        B.a_[2][0] = 0.0;
        B.a_[2][1] = (-2.0) * epsilon_s * a1n / (a2n * a2n);
        B.a_[2][2] = (-2.0) * epsilon_s * yn / (a2n * a2n);
        B.a_[2][3] = 4.0 * epsilon_s * yn * a1n / (std::pow(a2n, 3.0));

        B.a_[3][0] = (-2.0) * epsilon_s * a2n / (a1n * a1n);
        B.a_[3][1] = 0.0;
        B.a_[3][2] = 4.0 * epsilon_s * xn * a2n / (std::pow(a1n, 3.0));
        B.a_[3][3] = (-2.0) * epsilon_s * xn / (a1n * a1n);

        matrix E{4};
        E.make_unitary();

        matrix A{4};
        A = E + B * (-1.077) * STEP + B * B * 0.372 * STEP * STEP;
        vector solution = A.solve_with_gauss(f.v_);
        res[i] = res[i - 1] + solution * STEP;
    }

    return res;
}

std::vector<vector> calculate_modified()
{
    std::vector<vector> res(static_cast<size_t>(Tk / STEP));
    res[0].v_ = new double[4];
    res[0].n_ = 4;
    res[0].v_[0] = x0_m;
    res[0].v_[1] = y0_m;
    res[0].v_[2] = a10_m;
    res[0].v_[3] = a20_m;

    for (int i = 1; i < static_cast<size_t>(Tk / STEP); ++i)
    {
        res[i].v_ = new double[4];
        res[i].n_ = 4;
        // calculating right side
        vector func_u_n{4};
        double xn = res[i - 1].v_[0];
        double yn = res[i - 1].v_[1];
        double a1n = res[i - 1].v_[2];
        double a2n = res[i - 1].v_[3];
        func_u_n.v_[0] = xn * (2.0 * a1n - 0.5 * xn - (std::pow(a1n, 3.0)) / (std::pow(a2n, 3.0)) * yn);
        func_u_n.v_[1] = yn * (2.0 * a2n - 0.5 * yn - (std::pow(a2n, 3.0)) / (std::pow(a1n, 3.0)) * xn);
        func_u_n.v_[2] = epsilon_m * (2.0 - 3.0 * a1n * a1n / (std::pow(a2n, 3.0)) * yn);
        func_u_n.v_[3] = epsilon_m * (2.0 - 3.0 * a2n * a2n / (std::pow(a1n, 3.0)) * xn);
        vector func_arg = res[i - 1] + func_u_n * STEP * (-0.577);

        double xn_arg = func_arg.v_[0];
        double yn_arg = func_arg.v_[1];
        double a1n_arg = func_arg.v_[2];
        double a2n_arg = func_arg.v_[3];
        vector f{4};
        f.v_[0] = xn_arg * (2.0 * a1n_arg - 0.5 * xn_arg - (std::pow(a1n_arg, 3.0)) / (std::pow(a2n_arg, 3.0)) * yn_arg);
        f.v_[1] = yn_arg * (2.0 * a2n_arg - 0.5 * yn_arg - (std::pow(a2n_arg, 3.0)) / (std::pow(a1n_arg, 3.0)) * xn_arg);
        f.v_[2] = epsilon_m * (2.0 - 3.0 * a1n_arg * a1n_arg / (std::pow(a2n_arg, 3.0)) * yn_arg);
        f.v_[3] = epsilon_m * (2.0 - 3.0 * a2n_arg * a2n_arg / (std::pow(a1n_arg, 3.0)) * xn_arg);

        // calculating equation matrix
        matrix B{4};
        B.a_[0][0] = 2.0 * a1n - xn - (std::pow(a1n, 3.0)) / (std::pow(a2n, 3.0)) * yn;
        B.a_[0][1] = ((-1.0) * std::pow(a1n, 3.0) * xn) / (std::pow(a2n, 3.0));
        B.a_[0][2] = xn * (2.0 - 3.0 * (a1n * a1n * yn) / (std::pow(a2n, 3.0)));
        B.a_[0][3] = 3.0 * xn * yn * std::pow(a1n, 3.0) / (std::pow(a2n, 4.0));

        B.a_[1][0] = ((-1.0) * std::pow(a2n, 3.0) * yn) / (std::pow(a1n, 3.0));
        B.a_[1][1] = 2.0 * a2n - yn - (std::pow(a2n, 3.0)) / (std::pow(a1n, 3.0)) * xn;
        B.a_[1][2] = 3.0 * xn * yn * std::pow(a2n, 3.0) / (std::pow(a1n, 4.0));
        B.a_[1][3] = yn * (2.0 - 3.0 * (a2n * a2n * xn) / (std::pow(a1n, 3.0)));

        B.a_[2][0] = 0.0;
        B.a_[2][1] = (-3.0) * epsilon_m * a1n * a1n / (std::pow(a2n, 3.0));
        B.a_[2][2] = (-6.0) * epsilon_m * yn * a1n / (std::pow(a2n, 3.0));
        B.a_[2][3] = 9.0 * epsilon_m * yn * a1n * a1n / (std::pow(a2n, 4.0));

        B.a_[3][0] = (-3.0) * epsilon_m * a2n * a2n / (std::pow(a1n, 3.0));
        B.a_[3][1] = 0.0;
        B.a_[3][2] = 9.0 * epsilon_m * xn * a2n * a2n / (std::pow(a1n, 4.0));
        B.a_[3][3] = (-6.0) * epsilon_m * xn * a2n / (std::pow(a1n, 3.0));

        matrix E{4};
        E.make_unitary();

        matrix A{4};
        A = E + B * (-1.077) * STEP + B * B * 0.372 * STEP * STEP;
        vector solution = A.solve_with_gauss(f.v_);
        res[i] = res[i - 1] + solution * STEP;
    }

    return res;
}

std::ostream& operator<<(std::ostream& stream, const std::vector<vector>& points)
{
    stream.precision(5);
    stream << std::fixed;
    double time = 0;
    for (const auto& item: points)
    {
        for (int i = 0; i < item.n_; ++i)
        {
            stream << item.v_[i] << '\t';
        }
        stream << time << '\n';
        time += STEP;
    }

    return stream;
}