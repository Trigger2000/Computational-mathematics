#include "rk.h"

int main()
{
    std::vector<point> result_rk1 = rk1();
    std::vector<point> result_rk2 = rk2();
    std::vector<point> result_rk3 = rk3();
    std::vector<point> result_rk4 = rk4();

    std::ofstream file1("data1.dat");
    std::ofstream file2("data2.dat");
    std::ofstream file3("data3.dat");
    std::ofstream file4("data4.dat");

    file1 << result_rk1;
    file2 << result_rk2;
    file3 << result_rk3;
    file4 << result_rk4;
    
    file1.close();
    file2.close();
    file3.close();
    file4.close();
    
    return 0;
}