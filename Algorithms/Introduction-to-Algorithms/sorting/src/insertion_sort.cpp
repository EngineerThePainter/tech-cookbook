#include "insertion_sort.hpp"

namespace sorting
{
void InsertionSort::Sort(std::vector<int>& array_to_sort)
{
  for (int j = 1; j < array_to_sort.size(); ++j) {
    int key = array_to_sort[j];
    int i = j - 1;
    int number_of_iterations = 0;
    while (i > -1 && array_to_sort[i] > key) {
      ++number_of_iterations;
      ++number_of_assignements_;
      array_to_sort[i + 1] = array_to_sort[i];
      i -= 1;
    }
    number_of_comparisons_ += number_of_iterations +
                              1; // Additional one, because to check if we should start while we need to make comparison
    array_to_sort[i + 1] = key;
  }
}
} // namespace sorting
