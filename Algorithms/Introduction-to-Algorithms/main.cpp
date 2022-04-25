#include <exception>
#include <iostream>

#include "binary_search.hpp"
#include "bst.hpp"
#include "bubble_sort.hpp"
#include "counting_sort.hpp"
#include "demo_sorting.hpp"
#include "heap.hpp"
#include "heap_sort.hpp"
#include "insertion_sort.hpp"
#include "linked_list.hpp"
#include "matrix_multiply.hpp"
#include "maximum_subarray.hpp"
#include "merge_sort.hpp"
#include "merge_sort_improved.hpp"
#include "queue.hpp"
#include "quicksort.hpp"
#include "randomized_quicksort.hpp"
#include "rb_tree.hpp"
#include "stack.hpp"

#ifdef _DEBUG
#if _WIN32
#define WIN_MEMORY_LEAK_CHECKER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>
#endif // _WIN32
#endif // _DEBUG

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
  sorting::HeapSort heap_sort;
  sorting::demo_sorting(heap_sort);
  std::cout << "*****************************" << std::endl;
}

void quickSort()
{
  std::cout << "*** Quick sort\n";
  sorting::QuickSort quick_sort;
  sorting::demo_sorting(quick_sort);
  std::cout << "*****************************" << std::endl;
}

void randomizedQuickSort()
{
  std::cout << "*** Randomized Quick sort\n";
  sorting::RandomizedQuickSort randomized_quick_sort;
  sorting::demo_sorting(randomized_quick_sort);
  std::cout << "*****************************" << std::endl;
}

void countingSort()
{
  std::cout << "*** Counting sort\n";
  sorting::CountingSort counting_sort;
  sorting::demo_sorting(counting_sort);
  std::cout << "*****************************" << std::endl;
}

void sortingAlgorithms()
{
  std::cout << "***** Sorting algorithms\n";
  insertionSort();
  bubbleSort();
  mergeSort();
  mergeSortImproved();
  heapSort();
  /* Do not run it on big data as the "best case" causes stack overflow*/
  quickSort();
  randomizedQuickSort();
  countingSort();
  std::cout << "**********\n";
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

void stackUsage()
{
  std::cout << "*** Stack\n";
  data_structures::Stack stack(5);
  try {
    stack.pop();
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }

  stack.push(1);
  stack.push(2);
  stack.push(3);
  stack.push(4);
  stack.push(5);

  try {
    stack.push(6);
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }

  std::cout << stack.pop() << std::endl;
  std::cout << stack.pop() << std::endl;
  std::cout << stack.pop() << std::endl;

  std::cout << "*****************************" << std::endl;
}

void queueUsage()
{
  std::cout << "*** Queue\n";
  data_structures::Queue queue(3);
  queue.enqueue(1);
  queue.enqueue(2);
  queue.enqueue(3);
  queue.printQueue();
  queue.enqueue(4);
  queue.printQueue();
  std::cout << queue.dequeue() << std::endl;
  std::cout << "*****************************" << std::endl;
}

void linkedListUsage()
{
  std::cout << "*** Linked List\n";
  data_structures::LinkedList list;
  for (int i = 1; i <= 10; ++i) {
    list.insert(i, i * 100);
  }
  list.printList();
  auto elem = list.search(3);
  list.remove(elem);
  list.printList();
  if (elem == nullptr) {
    std::cout << "Elem was removed\n";
  }
  std::cout << "*****************************" << std::endl;
}

void bstUsage()
{
  std::cout << "*** BST\n";
  data_structures::BST bst;
  bst.insert(2, 20);
  bst.insert(1, 10);
  bst.insert(3, 30);
  bst.insert(10, 100);
  bst.insert(4, 40);
  bst.inorderTreeWalk();
  auto elem = bst.search(3);
  bst.remove(elem);
  bst.inorderTreeWalk();
  std::cout << "*****************************" << std::endl;
}

void rbTreeUsage()
{
  std::cout << "*** Red-Black Trees\n";
  data_structures::RBTree rbTree;
  rbTree.insert(2, 20);
  rbTree.insert(1, 10);
  rbTree.insert(3, 30);
  // rbTree.insert(10, 100);
  rbTree.insert(4, 40);
  rbTree.inorderTreeWalk();
  std::cout << "*****************************" << std::endl;
}

int main()
{
  std::cout << "***** Introduction to Algorithms 3rd edition" << std::endl << std::endl;
  sortingAlgorithms();

  binarySearch();

  maximumSubarray();

  matrixMultiplication();

  heapUsage();

  stackUsage();

  queueUsage();

  linkedListUsage();

  bstUsage();

  rbTreeUsage();

#ifdef WIN_MEMORY_LEAK_CHECKER
  _CrtDumpMemoryLeaks();
#endif // WIN_MEMORY_LEAK_CHECKER

  getchar();
  return 0;
}
