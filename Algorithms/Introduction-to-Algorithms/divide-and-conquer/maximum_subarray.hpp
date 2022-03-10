#ifndef DAC_MAXIMUM_SUBARRAY
#define DAC_MAXIMUM_SUBARRAY

#include <limits>
#include <vector>

namespace dac
{
struct Max_Subarray {
  int low_index = -1;
  int high_index = -1;
  int sum = -std::numeric_limits<int>::infinity();
};

void demoMaximumSubarray();

Max_Subarray findMaximumSubarray(std::vector<int>& A, int low_index, int high_index);

Max_Subarray findMaximumSubarrayBruteForce(std::vector<int>& A);

} // namespace dac

#endif