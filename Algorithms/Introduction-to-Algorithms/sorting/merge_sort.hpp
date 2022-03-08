#ifndef SORTING_MERGE_SORT_HPP
#define SORTING_MERGE_SORT_HPP

#include "sorting_algorithm.hpp"

namespace sorting
{
class MergeSort : public SortingAlgorithm
{
public:
  ~MergeSort() = default;
  void Sort(std::vector<int>& array_to_sort) override;

private:
  void Sort(std::vector<int>& A, int p, int r);
  void Merge(std::vector<int>& A, int p, int q, int r);
};
} // namespace sorting

#endif