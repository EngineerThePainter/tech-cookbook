#include "counting_sort.hpp"

#include <algorithm>
#include <iostream>

namespace sorting
{
void CountingSort::Sort(std::vector<int>& array_to_sort)
{
  int k = *std::max_element(array_to_sort.begin(), array_to_sort.end());
  std::vector<int> array_to_fill(array_to_sort.size(), 0);
  Sort(array_to_sort, array_to_fill, k);
  array_to_sort = array_to_fill;
}
void CountingSort::Sort(const std::vector<int>& in_array, std::vector<int>& out_array, const int k)
{
  std::vector<int> C(k + 1);

  for (unsigned int j = 0; j < in_array.size(); ++j) {
    C[in_array[j]] += 1;
  }

  for (unsigned int i = 1; i < C.size(); ++i) {
    C[i] += C[i - 1];
  }

  for (int j = in_array.size() - 1; j >= 0; --j) {
    out_array[C[in_array[j]]-1] = in_array[j];
    C[in_array[j]] -= 1;
  }
}
} // namespace sorting
