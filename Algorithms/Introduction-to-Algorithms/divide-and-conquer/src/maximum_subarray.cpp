#include "maximum_subarray.hpp"

#include <cmath>
#include <iostream>

namespace dac
{
namespace
{
Max_Subarray findMaximumCrossingSubarray(int* A, int low_index, int mid_index, int high_index)
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
  int test[16] = {-5, -22, 15, -4, 7, 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12};
  auto subarray = findMaximumSubarray(test, 0, 15);

  std::cout << subarray.low_index << " : " << subarray.high_index << " : " << subarray.sum << std::endl;
}

Max_Subarray findMaximumSubarray(int* A, int low_index, int high_index)
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
} // namespace dac