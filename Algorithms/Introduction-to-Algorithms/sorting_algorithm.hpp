#ifndef SORTING_ALGORITHM_HPP
#define SORTING_ALGORITHM_HPP

namespace sorting_algorithm
{

class SortingAlgorithm
{
public:
  virtual void Demo() final;
  virtual int* Sort(int* array_to_sort, int number_of_elements) = 0;

private:
  int number_of_comparisons_ = 0;
  int number_of_moves_ = 0;
};

} // namespace sorting_algorithm
#endif // SORTING_ALGORITHM_HPP