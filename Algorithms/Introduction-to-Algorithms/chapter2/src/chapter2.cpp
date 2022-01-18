#include "chapter2.hpp"

namespace chapters {
  void test(int x, double y) {
    for (int i = 0; i < 1000000; ++i) {
      x += y;
    }
  }
}