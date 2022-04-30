#ifndef SORTING_RANDOMIZED_QUICK_SORT_HPP
#define SORTING_RANDOMIZED_QUICK_SORT_HPP

#include "quicksort.hpp"

namespace sorting
{
class RandomizedQuickSort : public QuickSort
{
public:
  ~RandomizedQuickSort() = default;
  void Sort(std::vector<int>& array_to_sort) override;

private:
  void Sort(std::vector<int>& array_to_sort, const int p, const int r) override;
  int Partition(std::vector<int>& array_to_sort, const int p, const int r) override;
};
} // namespace sorting

#endif
