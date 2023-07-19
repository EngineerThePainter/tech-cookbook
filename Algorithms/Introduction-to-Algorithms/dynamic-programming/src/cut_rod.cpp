#include "cut_rod.hpp"

#include <iostream>
#include <limits>
#include <vector>

namespace dynamic_programming
{
namespace
{
int cutRod(const std::array<int, PRICES_SIZE>& prices, const int& rodLength)
{
  if (rodLength == 0) {
    return 0;
  }

  int q = -std::numeric_limits<int>::infinity();
  for (int i = 1; i <= rodLength; ++i) {
    int val = prices[i] + cutRod(prices, rodLength - i);
    q = val > q ? val : q;
  }
  return q;
}

int memoizedCutRodAux(const std::array<int, PRICES_SIZE>& prices, const int& rodLength, std::vector<int>& r)
{
  if (r[rodLength] >= 0) {
    return r[rodLength];
  }
  int q = 0;
  if (rodLength != 0) {
    q = -std::numeric_limits<int>::infinity();
    for (int i = 1; i <= rodLength; ++i) {
      int val = prices[i] + memoizedCutRodAux(prices, rodLength - i, r);
      q = val > q ? val : q;
    }
  }
  r[rodLength] = q;
  return q;
}

} // namespace

void cutRodRecursively(const std::array<int, PRICES_SIZE>& prices, const int& rodLength)
{
  if (rodLength > PRICES_SIZE) {
    return;
  }
  int rodMaximumValue = cutRod(prices, rodLength);
  std::cout << "For rod of length: " << rodLength << " we should got maximum revenue of: " << rodMaximumValue
            << std::endl;
}

void memoizedCutRod(const std::array<int, PRICES_SIZE>& prices, const int& rodLength)
{
  std::vector<int> r(rodLength+1, -1);
  int rodMaximumValue = memoizedCutRodAux(prices, rodLength, r);
  std::cout << "For rod of length: " << rodLength << " we should got maximum revenue of: " << rodMaximumValue
            << std::endl;
}

void bottomUpCutRod(const std::array<int, PRICES_SIZE>& prices, const int& rodLength) {
  std::vector<int> r(rodLength + 1, -1);
  r[0] = 0;
  for (int j = 1; j <= rodLength; ++j) {
    int q = -std::numeric_limits<int>::infinity();
    for (int i = 1; i <= j; ++i) {
      int val = prices[i] + r[j - i];
      q = val > q ? val : q;
    }
    r[j] = q;
  }
  std::cout << "For rod of length: " << rodLength << " we should got maximum revenue of: " << r[rodLength]
            << std::endl;
}
} // namespace dynamic_programming
