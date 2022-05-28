#ifndef DYNAMIC_PROGRAMMING_CUT_ROD_HPP
#define DYNAMIC_PROGRAMMING_CUT_ROD_HPP

#include <array>

namespace dynamic_programming
{

class CutRodData
{
public:
  static const std::array<int, 11> ROD_PRICES{{0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30}};
};

void cutRodRecursively(const std::array<int, 11>& prices, const int& rodLength);
void memoizedCutRod(const std::array<int, 11>& prices, const int& rodLength);
void bottomUpCutRod(const std::array<int, 11>& prices, const int& rodLength);

} // namespace dynamic_programming

#endif // !DYNAMIC_PROGRAMMING_CUT_ROD_HPP
