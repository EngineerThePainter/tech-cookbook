#ifndef SORTING_COUNTING_SORT_HPP
#define SORTING_COUNTING_SORT_HPP

#include "sorting_algorithm.hpp"

namespace sorting
{
class CountingSort : public SortingAlgorithm
{
public:
  ~CountingSort() = default;
  void Sort(std::vector<int>& array_to_sort) override;

  private:
  void Sort(const std::vector<int>& in_array, std::vector<int>& out_array, const int k);
};
} // namespace sorting

#endif
