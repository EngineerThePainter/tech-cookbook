#include "designated_initializer.hpp"

#include <iostream>

namespace
{

struct A {
  int x;
  int y;
};

class B
{
public:
  // B(int x, float y) : x_(x), y_(y) {}
  int x_;
  float y_;
};

} // namespace

void showDesignatedInitializers()
{
  std::cout << "Initializing struct\n";
  A a{.x = 51, .y = 42};
  std::cout << "a.x: " << a.x << " "
            << " a.y: " << a.y << std::endl;
  std::cout << "Initializing class\n";
  B b{.x_ = 52, .y_ = 42.0};
  std::cout << "b.x: " << b.x_ << " "
            << " b.y: " << b.y_ << std::endl;
}