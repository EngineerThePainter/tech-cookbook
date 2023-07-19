#include "longest_common_subsequence.hpp"

#include <iostream>

namespace dynamic_programming
{
std::vector<std::vector<LCSTableElem>> lcsLength(const std::vector<int>& x, const std::vector<int>& y)
{
  const int m = x.size();
  const int n = y.size();

  std::vector<std::vector<LCSTableElem>> b(m + 1, std::vector<LCSTableElem>(n + 1));
  for (int i = 0; i <= m; ++i) {
    b[i][0] = {0, LCSTableDirection::LEFT};
  }
  for (int i = 0; i <= n; ++i) {
    b[0][i] = {0, LCSTableDirection::LEFT};
  }

  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (x[i-1] == y[j-1]) {
        b[i][j] = {b[i - 1][j - 1].val + 1, LCSTableDirection::UP_LEFT};
      } else if (b[i - 1][j].val >= b[i][j - 1].val) {
        b[i][j] = {b[i - 1][j].val, LCSTableDirection::UP};
      } else {
        b[i][j] = {b[i][j - 1].val, LCSTableDirection::LEFT};
      }
    }
  }

  return b;
}

void printLcs(const std::vector<std::vector<LCSTableElem>>& b, const std::vector<int>& x, const int i, const int j)
{
  if (i == 0 || j == 0) {
    std::cout << "\n";
    return;
  }
  if (b[i][j].direction == LCSTableDirection::UP_LEFT) {
    printLcs(b, x, i - 1, j - 1);
    std::cout << x[i-1] << ", ";
  } else if (b[i][j].direction == LCSTableDirection::UP) {
    printLcs(b, x, i - 1, j);
  } else {
    printLcs(b, x, i, j - 1);
  }
}
} // namespace dynamic_programming
