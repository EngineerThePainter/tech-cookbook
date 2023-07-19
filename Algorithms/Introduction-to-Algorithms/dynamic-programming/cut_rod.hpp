#ifndef DYNAMIC_PROGRAMMING_CUT_ROD_HPP
#define DYNAMIC_PROGRAMMING_CUT_ROD_HPP

#include <array>

namespace dynamic_programming
{

constexpr int PRICES_SIZE = 21;
const constexpr std::array<int, PRICES_SIZE> ROD_PRICES = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30, 32, 33, 35, 38, 42, 42, 45, 46, 47, 48};

void cutRodRecursively(const std::array<int, PRICES_SIZE>& prices, const int& rodLength);
void memoizedCutRod(const std::array<int, PRICES_SIZE>& prices, const int& rodLength);
void bottomUpCutRod(const std::array<int, PRICES_SIZE>& prices, const int& rodLength);

} // namespace dynamic_programming

#endif // !DYNAMIC_PROGRAMMING_CUT_ROD_HPP
