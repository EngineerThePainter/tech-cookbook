#include <iostream>

#include "binary_search.hpp"
#include "bubble_sort.hpp"
#include "demo_sorting.hpp"
#include "insertion_sort.hpp"
#include "merge_sort.hpp"
#include "merge_sort_improved.hpp"

int main()
{
  std::cout << "***** Introduction to Algorithms 3rd edition" << std::endl << std::endl;

  std::cout << "*** Insertion sort\n";
  sorting::InsertionSort insertion_sort;
  sorting::demo_sorting(insertion_sort);
  std::cout << "*****************************" << std::endl;

  std::cout << "*** Bubble sort\n";
  sorting::BubbleSort bubble_sort;
  sorting::demo_sorting(bubble_sort);
  std::cout << "*****************************" << std::endl;

  std::cout << "*** Merge sort\n";
  sorting::MergeSort merge_sort;
  sorting::demo_sorting(merge_sort);
  std::cout << "*****************************" << std::endl;

  std::cout << "*** Merge sort improved\n";
  sorting::MergeSortImproved merge_sort_improved;
  sorting::demo_sorting(merge_sort_improved);
  std::cout << "*****************************" << std::endl;

  std::cout << "*** Binary search\n";
  searching::demoSearch();
  std::cout << "*****************************" << std::endl;
  return 0;
}