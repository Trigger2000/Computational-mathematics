#include "rozenbrok.h"

int main()
{
    std::vector<vector> simple_model = calculate_plain();
    std::vector<vector> modified_model = calculate_modified();

    std::ofstream file1("data1.dat");
    std::ofstream file2("data2.dat");

    file1 << simple_model;
    file2 << modified_model;

    file1.close();
    file2.close();

    return 0;
}