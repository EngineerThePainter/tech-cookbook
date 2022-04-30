#include "quicksort.hpp"

namespace sorting
{

void QuickSort::Sort(std::vector<int>& array_to_sort) { Sort(array_to_sort, 0, array_to_sort.size() - 1); }

void QuickSort::Sort(std::vector<int>& array_to_sort, const int p, const int r)
{
  if (p < r) {
    int q = Partition(array_to_sort, p, r);
    Sort(array_to_sort, p, q - 1);
    Sort(array_to_sort, q + 1, r);
  }
}

int QuickSort::Partition(std::vector<int>& array_to_sort, const int p, const int r)
{
  int x = array_to_sort[r];
  int i = p - 1;
  for (int j = p; j <= r - 1; j++) {
    number_of_comparisons_++;
    if (array_to_sort[j] <= x) {
      i++;
      int temp = array_to_sort[j];
      number_of_assignements_++;
      array_to_sort[j] = array_to_sort[i];
      number_of_assignements_++;
      array_to_sort[i] = temp;
    }
  }
  int temp = array_to_sort[r];
  number_of_assignements_++;
  array_to_sort[r] = array_to_sort[i + 1];
  number_of_assignements_++;
  array_to_sort[i + 1] = temp;
  return i + 1;
}

} // namespace sorting
