#include "merge_sort_improved.hpp"

#include <iostream>

namespace sorting
{

namespace
{
constexpr int SIZE_BOUNDARY = 10;
}

void MergeSortImproved::Sort(std::vector<int>& array_to_sort)
{
  Sort(array_to_sort, 1, array_to_sort.size());
}

void MergeSortImproved::Sort(std::vector<int>& A, int p, int r)
{
  if (p < r) {
    // This is a floor operation
    int q = (p + r) / 2;
    Sort(A, p, q);
    Sort(A, q + 1, r);
    if (r - p < SIZE_BOUNDARY) {
      InsertionSort(A, p, r);
    } else {
      Merge(A, p, q, r);
    }
  }
}

void MergeSortImproved::Merge(std::vector<int>& A, int p, int q, int r)
{
  int n1 = q - p + 1;
  int n2 = r - q;

  std::vector<int> L;
  L.resize(n1);
  std::vector<int> R;
  R.resize(n2);
  for (int i = 0; i < n1; ++i) {
    L[i] = A[p + i - 1];
  }

  for (int i = 0; i < n2; ++i) {
    R[i] = A[q + i];
  }

  for (int k = p - 1, i = 0, j = 0; k < r; ++k) {
    if (i >= n1) {
      ++number_of_assignements_;
      A[k] = R[j];
      ++j;
      continue;
    }

    if (j >= n2) {
      ++number_of_assignements_;
      A[k] = L[i];
      ++i;
      continue;
    }

    ++number_of_comparisons_;
    if (L[i] <= R[j]) {
      ++number_of_assignements_;
      A[k] = L[i];
      ++i;
    } else {
      ++number_of_assignements_;
      A[k] = R[j];
      ++j;
    }
  }
}

void MergeSortImproved::InsertionSort(std::vector<int>& A, int left, int right)
{
  for (int j = left; j < right; ++j) {
    int key = A[j];
    int i = j - 1;
    int number_of_iterations = 0;
    while (i >= left - 1 && A[i] > key) {
      ++number_of_iterations;
      ++number_of_assignements_;
      A[i + 1] = A[i];
      i -= 1;
    }
    // Additional one, because to check if we should start while we need to make comparison
    number_of_comparisons_ += number_of_iterations + 1;
    A[i + 1] = key;
  }
}

} // namespace sorting