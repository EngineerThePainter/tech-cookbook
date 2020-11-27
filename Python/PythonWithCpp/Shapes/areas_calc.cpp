#include "areas_calc.hpp"
#include <cassert>

double rectangle_area(const double x, const double y) {
    assert(x > 0);
    assert(y > 0);
    return x * y;
}