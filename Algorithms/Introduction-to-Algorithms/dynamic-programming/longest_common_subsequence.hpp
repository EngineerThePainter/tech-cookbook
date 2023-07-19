#ifndef DYNAMIC_PROGRAMMING_LONGEST_COMMON_SUBSEQUENCE_HPP
#define DYNAMIC_PROGRAMMING_LONGEST_COMMON_SUBSEQUENCE_HPP

#include <vector>

namespace dynamic_programming
{
enum class LCSTableDirection { UP=0, UP_LEFT, LEFT };

struct LCSTableElem {
  int val;
  LCSTableDirection direction;
};

std::vector<std::vector<LCSTableElem>> lcsLength(const std::vector<int>& x, const std::vector<int>& y);
void printLcs(const std::vector<std::vector<LCSTableElem>>& b, const std::vector<int>& x, const int i, const int j);
} // namespace dynamic_programming

#endif // DYNAMIC_PROGRAMMING_LONGEST_COMMON_SUBSEQUENCE_HPP
