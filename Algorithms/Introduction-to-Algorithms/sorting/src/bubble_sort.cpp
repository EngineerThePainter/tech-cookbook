#include "bubble_sort.hpp"

namespace sorting
{
void BubbleSort::Sort(std::vector<int>& array_to_sort)
{
  for (int i = 0; i < array_to_sort.size(); ++i) {
    for (int j = array_to_sort.size() - 1; j >= i + 1; --j) {
      ++number_of_comparisons_;
      if (array_to_sort[j] < array_to_sort[j - 1]) {
        int temp = array_to_sort[j];
        ++number_of_assignements_;
        array_to_sort[j] = array_to_sort[j - 1];
        ++number_of_assignements_;
        array_to_sort[j - 1] = temp;
      }
    }
  }
}
} // namespace sorting