#include "binary_search.hpp"

#include <cmath>
#include <functional>
#include <iostream>

#include "time_tracker.hpp"

namespace searching
{
void demoSearch()
{
  constexpr int nb_elements = 100000;
  int* search_case = new int[nb_elements];
  for (int i = 0; i < nb_elements; ++i) {
    search_case[i] = i + 1;
  }
  std::function<void(int*, int, int, SearchData&)> search = [&](int* A, int left_boundary, int right_boundary,
                                                                SearchData& data) {
    binarySearch(A, left_boundary, right_boundary, data);
  };

  SearchData first_value_data{1, 0, -1};
  std::cout << "First value case: "
            << utils::runWithTimeMeasure(search, search_case, 0, nb_elements - 1, first_value_data).count()
            << " milliseconds" << std::endl;
  std::cout << "First value comparisons: " << first_value_data.number_of_comparisons << std::endl;
  std::cout << "First value index: " << first_value_data.found_index << std::endl;

  SearchData middle_case_data{nb_elements / 2, 0, -1};
  std::cout << "Middle value case: "
            << utils::runWithTimeMeasure(search, search_case, 0, nb_elements - 1, middle_case_data).count()
            << " milliseconds" << std::endl;
  std::cout << "Middle value comparisons: " << middle_case_data.number_of_comparisons << std::endl;
  std::cout << "middle value index: " << middle_case_data.found_index << std::endl;

  SearchData last_value_data{nb_elements, 0, -1};
  std::cout << "Last value case: "
            << utils::runWithTimeMeasure(search, search_case, 0, nb_elements - 1, last_value_data).count()
            << " milliseconds" << std::endl;
  std::cout << "Last value case comparisons: " << last_value_data.number_of_comparisons << std::endl;
  std::cout << "Last value case index: " << last_value_data.found_index << std::endl;

  delete[] search_case;
}

void binarySearch(int* A, int left_boundary, int right_boundary, SearchData& data)
{
  // std::cout << "Call " << left_boundary << " : " << right_boundary << std::endl;
  if (left_boundary < right_boundary) {
    int middle = std::floor((left_boundary + right_boundary) / 2);
    // std::cout << "Middle: " << middle << std::endl;
    ++data.number_of_comparisons;
    if (data.searching_value > A[middle]) {
      binarySearch(A, middle + 1, right_boundary, data);
    } else {
      binarySearch(A, left_boundary, middle, data);
    }
  } else {
    data.found_index = left_boundary;
  }
}
} // namespace searching