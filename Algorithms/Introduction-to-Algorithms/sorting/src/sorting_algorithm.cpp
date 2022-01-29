#include "sorting_algorithm.hpp"

namespace sorting
{
int SortingAlgorithm::NumberOfComparisons() const { return number_of_comparisons_; }
int SortingAlgorithm::NumberOfAssignements() const { return number_of_assignements_; }
void SortingAlgorithm::ResetCounters()
{
  number_of_comparisons_ = 0;
  number_of_assignements_ = 0;
}
} // namespace sorting