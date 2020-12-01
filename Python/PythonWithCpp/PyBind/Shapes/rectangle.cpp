#include "rectangle.hpp"

#include <cassert>

namespace shapes {

Rectangle::Rectangle(const double x, const double y, const double width, const double height)
:x(x),
 y(y),
 width(width),
 height(height)
{
    assert(width > 0);
    assert(height > 0);
}

void Rectangle::setX(const double x) {
    this->x = x;
}

void Rectangle::setY(const double y) {
    this->y = y;
}

void Rectangle::setWidth(const double width) {
    assert(width > 0);
    this->width = width;
}

void Rectangle::setHeight(const double height) {
    assert(height > 0);
    this->height = height;
}

std::vector<Rectangle> getRectangles() {
    constexpr double width = 14;
    constexpr double height = 4;
    std::vector<Rectangle> rectangles;
    for (int x = 0; x < 5; ++x) {
        for (int y = 0; y < 3; ++y) {
            rectangles.emplace_back(x, y, width, height);
        }
    }
    return rectangles;
}

} // namespace shapes