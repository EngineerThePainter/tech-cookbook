#include "sorting_algorithm.hpp"

namespace sorting
{
int SortingAlgorithm::NumberOfComparisons() const { return number_of_comparisons_; }
int SortingAlgorithm::NumberOfMoves() const { return number_of_moves_; }
void SortingAlgorithm::ResetCounters()
{
  number_of_comparisons_ = 0;
  number_of_moves_ = 0;
}
} // namespace sorting