#ifndef SORTING_QUICK_SORT_HPP
#define SORTING_QUICK_SORT_HPP

#include "sorting_algorithm.hpp"

namespace sorting
{
class QuickSort : public SortingAlgorithm
{
public:
  ~QuickSort() = default;
  void Sort(std::vector<int>& array_to_sort) override;

protected:
  virtual void Sort(std::vector<int>& array_to_sort, const int p, const int r);
  virtual int Partition(std::vector<int>& array_to_sort, const int p, const int r);
};
} // namespace sorting

#endif
