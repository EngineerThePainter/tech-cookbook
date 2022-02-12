#ifndef DAC_MAXIMUM_SUBARRAY
#define DAC_MAXIMUM_SUBARRAY

#include <limits>

namespace dac
{
struct Max_Subarray {
  int low_index = -1;
  int high_index = -1;
  int sum = -std::numeric_limits<int>::infinity();
};

void demoMaximumSubarray();

Max_Subarray findMaximumSubarray(int* A, int low_index, int high_index);

} // namespace dac

#endif