#include "merge_sort.hpp"

#include <iostream>

namespace sorting
{

void MergeSort::Sort(std::vector<int>& array_to_sort)
{
  Sort(array_to_sort, 1, array_to_sort.size());
}
void MergeSort::Sort(std::vector<int>& A, int p, int r)
{
  if (p < r) {
    // This is a floor operation
    int q = (p + r) / 2;
    Sort(A, p, q);
    Sort(A, q + 1, r);
    Merge(A, p, q, r);
  }
}
void MergeSort::Merge(std::vector<int>& A, int p, int q, int r)
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
} // namespace sorting