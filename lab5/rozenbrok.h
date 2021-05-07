#pragma once

#include "vector.h"
#include "matrix.h"
#include <fstream>
#include <vector>

#define STEP 0.001
#define Tk 2000.0

#define epsilon_s 0.001
#define x0_s 40.0
#define y0_s 30.0
#define a10_s -10000000000000
#define a20_s 10.0

#define epsilon_m 0.01
#define x0_m 40.0
#define y0_m 10.0
#define a10_m -100
#define a20_m 10.0

std::vector<vector> calculate_plain();
std::vector<vector> calculate_modified();
std::ostream& operator<<(std::ostream& stream, const std::vector<vector>& points);