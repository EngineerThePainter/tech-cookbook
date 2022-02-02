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
  void Sort(int* array_to_sort, int number_of_elements) override;

private:
  void Sort(int* A, int p, int r);
  void Merge(int* A, int p, int q, int r);
  void InsertionSort(int* A, int left, int right);
};
} // namespace sorting

#endif