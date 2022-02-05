#include "bubble_sort.hpp"

namespace sorting
{
void BubbleSort::Sort(int* array_to_sort, int number_of_elements)
{
  for (int i = 0; i < number_of_elements; ++i) {
    for (int j = number_of_elements - 1; j >= i + 1; --j) {
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