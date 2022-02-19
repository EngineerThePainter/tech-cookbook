#ifndef DAC_MAXIMUM_SUBARRAY
#define DAC_MAXIMUM_SUBARRAY

#include <limits>

// TODO: Brute force mechanism
// Valid demo

namespace dac
{
struct Max_Subarray {
  int low_index = -1;
  int high_index = -1;
  int sum = -std::numeric_limits<int>::infinity();
};

void demoMaximumSubarray();

Max_Subarray findMaximumSubarray(int* A, int low_index, int high_index);

Max_Subarray findMaximumSubarrayBruteForce(int* A, int number_of_elements);

} // namespace dac

#endif