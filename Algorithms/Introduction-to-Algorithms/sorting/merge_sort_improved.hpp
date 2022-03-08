#ifndef SORTING_MERGE_SORT_IMPROVED_HPP
#define SORTING_MERGE_SORT_IMPROVED_HPP

#include "insertion_sort.hpp"
#include "sorting_algorithm.hpp"

namespace sorting
{
class MergeSortImproved : public SortingAlgorithm
{
public:
  ~MergeSortImproved() = default;
  void Sort(std::vector<int>& array_to_sort) override;

private:
  void Sort(std::vector<int>& A, int p, int r);
  void Merge(std::vector<int>& A, int p, int q, int r);
  void InsertionSort(std::vector<int>& A, int left, int right);
};
} // namespace sorting

#endif