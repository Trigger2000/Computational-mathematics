#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <iomanip>

const double STEP = 0.001;

struct point 
{
    double x = 0, y = 0, z = 0;
    double u = 0;
    double t = 0;
};

std::ostream& operator<<(std::ostream& stream, const std::vector<point> points);
void initialize (std::vector<point>& points);
std::vector<point> rk1 ();
std::vector<point> rk2 ();
std::vector<point> rk3 ();
std::vector<point> rk4 ();