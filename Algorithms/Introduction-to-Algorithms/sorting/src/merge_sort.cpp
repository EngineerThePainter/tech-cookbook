#include "merge_sort.hpp"

#include <iostream>

namespace sorting
{

void MergeSort::Sort(int* array_to_sort, int number_of_elements) { Sort(array_to_sort, 0, number_of_elements); }
void MergeSort::Sort(int* A, int p, int r)
{
  if (p < r) {
    int q = (p + r) / 2;
    Sort(A, p, q);
    Sort(A, q + 1, r);
    Merge(A, p, q, r);
  }
}
void MergeSort::Merge(int* A, int p, int q, int r)
{
  int n1 = q - p;
  int n2 = r - q;
  int* L = new int[n1];
  int* R = new int[n2];
  for (int i = 0; i < n1; ++i) {
    L[i] = A[p + i];
  }

  for (int i = 0; i < n2; ++i) {
    R[i] = A[q + i];
  }

  for (int k = p, i = 0, j = 0; k < r; ++k) {
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
  delete[] L;
  delete[] R;
}
} // namespace sorting