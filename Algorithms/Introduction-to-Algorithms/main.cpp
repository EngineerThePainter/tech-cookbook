#include <iostream>

#include "binary_search.hpp"
#include "bubble_sort.hpp"
#include "demo_sorting.hpp"
#include "heap.hpp"
#include "heap_sort.hpp"
#include "insertion_sort.hpp"
#include "matrix_multiply.hpp"
#include "maximum_subarray.hpp"
#include "merge_sort.hpp"
#include "merge_sort_improved.hpp"

void insertionSort()
{
  std::cout << "*** Insertion sort\n";
  sorting::InsertionSort insertion_sort;
  sorting::demo_sorting(insertion_sort);
  std::cout << "*****************************" << std::endl;
}

void bubbleSort()
{
  std::cout << "*** Bubble sort\n";
  sorting::BubbleSort bubble_sort;
  sorting::demo_sorting(bubble_sort);
  std::cout << "*****************************" << std::endl;
}

void mergeSort()
{
  std::cout << "*** Merge sort\n";
  sorting::MergeSort merge_sort;
  sorting::demo_sorting(merge_sort);
  std::cout << "*****************************" << std::endl;
}

void mergeSortImproved()
{
  std::cout << "*** Merge sort improved\n";
  sorting::MergeSortImproved merge_sort_improved;
  sorting::demo_sorting(merge_sort_improved);
  std::cout << "*****************************" << std::endl;
}

void heapSort()
{
  std::cout << "*** Heap sort\n";
  sorting::MergeSortImproved merge_sort_improved;
  sorting::demo_sorting(merge_sort_improved);
  std::cout << "*****************************" << std::endl;
}


void binarySearch()
{
  std::cout << "*** Binary search\n";
  searching::demoSearch();
  std::cout << "*****************************" << std::endl;
}

void maximumSubarray()
{
  std::cout << "*** Maximum subarray\n";
  dac::demoMaximumSubarray();
  std::cout << "*****************************" << std::endl;
}

void matrixMultiplication()
{
  std::cout << "*** Matrix multiplication\n";
  matrix::demoMatrixMultiplication();
  std::cout << "*****************************" << std::endl;
}

void heapUsage()
{
  std::cout << "*** Heaps\n";
  std::vector<int> v{1, 2, 3, 4, 5};
  heap::Heap<int> h(v);
  h.PrintHeap();
  std::cout << "Build max heap\n";
  heap::BuildMaxHeap<int>(h);
  h.PrintHeap();
  std::cout << "*****************************" << std::endl;
}

int main()
{
  std::cout << "***** Introduction to Algorithms 3rd edition" << std::endl << std::endl;
  insertionSort();
  bubbleSort();
  mergeSort();
  mergeSortImproved();
  heapSort();

  binarySearch();

  maximumSubarray();

  matrixMultiplication();

  //heapUsage();

  getchar();
  return 0;
}
