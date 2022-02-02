#include "sorting_algorithm.hpp"

namespace sorting
{
long long SortingAlgorithm::NumberOfComparisons() const { return number_of_comparisons_; }
long long SortingAlgorithm::NumberOfAssignements() const { return number_of_assignements_; }
void SortingAlgorithm::ResetCounters()
{
  number_of_comparisons_ = 0;
  number_of_assignements_ = 0;
}
} // namespace sorting