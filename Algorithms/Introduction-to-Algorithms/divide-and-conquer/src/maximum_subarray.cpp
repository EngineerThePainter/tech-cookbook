#include "maximum_subarray.hpp"

#include <cmath>
#include <iostream>

namespace dac
{
namespace
{
Max_Subarray findMaximumCrossingSubarray(std::vector<int>& A, int low_index, int mid_index, int high_index)
{
  Max_Subarray subarray;
  int left_sum = -std::numeric_limits<int>::infinity();
  int sum = 0;
  for (int i = mid_index; i >= low_index; --i) {
    sum += A[i];
    if (sum > left_sum) {
      left_sum = sum;
      subarray.low_index = i;
    }
  }
  int right_sum = -std::numeric_limits<int>::infinity();
  sum = 0;
  for (int j = mid_index + 1; j <= high_index; ++j) {
    sum += A[j];
    if (sum > right_sum) {
      right_sum = sum;
      subarray.high_index = j;
    }
  }
  subarray.sum = left_sum + right_sum;
  return subarray;
}
} // namespace
void demoMaximumSubarray()
{
  std::vector<int> test = {-5, -22, 15, -4, 7, 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12};

  std::cout << "Brute force\n";
  auto subarray_brute_force = findMaximumSubarrayBruteForce(test);
  std::cout << "" << subarray_brute_force.low_index << " : " << subarray_brute_force.high_index << " : "
            << subarray_brute_force.sum << std::endl;

  auto subarray = findMaximumSubarray(test, 0, 15);
  std::cout << "Recursive case\n";

  std::cout << "" << subarray.low_index << " : " << subarray.high_index << " : " << subarray.sum << std::endl;
}

Max_Subarray findMaximumSubarray(std::vector<int>& A, int low_index, int high_index)
{
  if (high_index == low_index) {
    return {low_index, high_index, A[low_index]};
  } else {
    int mid_index = std::floor((low_index + high_index) / 2);
    Max_Subarray left_side = findMaximumSubarray(A, low_index, mid_index);
    Max_Subarray right_side = findMaximumSubarray(A, mid_index + 1, high_index);
    Max_Subarray cross_array = findMaximumCrossingSubarray(A, low_index, mid_index, high_index);
    if (left_side.sum >= right_side.sum && left_side.sum >= cross_array.sum) {
      return left_side;
    } else if (right_side.sum >= left_side.sum && right_side.sum >= cross_array.sum) {
      return right_side;
    }
    return cross_array;
  }
}

Max_Subarray findMaximumSubarrayBruteForce(std::vector<int>& A)
{
  Max_Subarray max_subarray;

  for (int i = 0; i < A.size(); ++i) {
    int sum = 0;
    for (int j = i; j < A.size(); ++j) {
      sum += A[j];
      if (sum > max_subarray.sum) {
        max_subarray.sum = sum;
        max_subarray.low_index = i;
        max_subarray.high_index = j;
      }
    }
  }
  return max_subarray;
}
} // namespace dac