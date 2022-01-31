#ifndef SEARCHING_BINARY_SEARCH
#define SEARCHING_BINARY_SEARCH

namespace searching
{

struct SearchData {
  int searching_value;
  int number_of_comparisons{0};
  int number_of_calls{0};
  int found_index = -1;
};

void demoSearch();

void binarySearch(int* A, int left_boundary, int right_boundary, SearchData& data);

} // namespace searching

#endif