#include "randomized_quicksort.hpp"
#include "quicksort.hpp"

#include <random>

namespace sorting
{

void RandomizedQuickSort::Sort(std::vector<int>& array_to_sort) { Sort(array_to_sort, 0, array_to_sort.size() - 1); }

void RandomizedQuickSort::Sort(std::vector<int>& array_to_sort, const int p, const int r)
{
  if (p < r) {
    int q = Partition(array_to_sort, p, r);
    Sort(array_to_sort, p, q - 1);
    Sort(array_to_sort, q + 1, r);
  }
}

int RandomizedQuickSort::Partition(std::vector<int>& array_to_sort, const int p, const int r)
{
  std::default_random_engine generator{};
  generator.seed(42);
  std::uniform_int_distribution<int> distr(p, r);
  int i = distr(generator);
  int temp = array_to_sort[i];
  array_to_sort[i] = array_to_sort[r];
  array_to_sort[r] = temp;
  number_of_assignements_ += 2;
  return QuickSort::Partition(array_to_sort, p, r);
}

} // namespace sorting
