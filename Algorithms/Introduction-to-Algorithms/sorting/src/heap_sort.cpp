#include "heap_sort.hpp"

#include "heap.hpp"

namespace sorting
{
void HeapSort::Sort(std::vector<int>& array_to_sort)
{
  heap::Heap<int> h(array_to_sort);
  heap::BuildMaxHeap(h);
  for (int i = h.Data().size() - 1; i >= 1; i--) {
    int temp = h.Data()[i];
    h.IncrementAssignements();
    h.Data()[i] = h.Data()[0];
    h.IncrementAssignements();
    h.Data()[0] = temp;
    h.HeapSize() = h.HeapSize() - 1;
    heap::MaxHeapify(h, 0);
  }
  array_to_sort = std::move(h.Data());
  number_of_assignements_ = h.Assignements();
  number_of_comparisons_ = h.Comparisons();
}

} // namespace sorting
