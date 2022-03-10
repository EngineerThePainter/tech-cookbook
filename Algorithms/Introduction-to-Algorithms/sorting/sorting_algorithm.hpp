#ifndef SORTING_ALGORITHM_HPP
#define SORTING_ALGORITHM_HPP

#include <vector>

namespace sorting
{

class SortingAlgorithm
{
public:
  virtual ~SortingAlgorithm() = default;
  virtual void Sort(std::vector<int>& array_to_sort) = 0;
  long long NumberOfComparisons() const;
  long long NumberOfAssignements() const;
  void ResetCounters();

protected:
  long long number_of_comparisons_ = 0;
  long long number_of_assignements_ = 0;
};

} // namespace sorting
#endif // SORTING_ALGORITHM_HPP