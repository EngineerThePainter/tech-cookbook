#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <vector>

namespace shapes {

class Rectangle {
public:
    Rectangle(const double x, const double y, const double width, const double height);
    double getX() const {return x;}
    double getY() const {return y;}
    double getWidth() const {return width;}
    double getHeight() const {return height;}

    void setX(const double x);
    void setY(const double y);
    void setWidth(const double width);
    void setHeight(const double height);

private:
    double x, y;
    double width, height;
};

std::vector<Rectangle> getRectangles();

} // namespace shapes
#endif // RECTANGLE_HPP