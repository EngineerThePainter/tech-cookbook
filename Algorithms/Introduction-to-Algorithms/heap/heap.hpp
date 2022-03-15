#ifndef HEAP_HEAP_HPP
#define HEAP_HEAP_HPP

#include <vector>

namespace heap
{
inline int ParentIndex(const int i) { return i / 2; }
inline int LeftIndex(const int i) { return 2 * i; }
inline int RightIndex(const int i) { return LeftIndex(i) + 1; }

template <typename T> struct Heap {
  std::vector<T> data;
  int heap_size = 0;

  static MaxHeapify(Heap<T>& heap, const int i)
  {
    const int left = LeftIndex(i);
    const int right = RightIndex(i);
    int largest = -1;
    if (left <= heap.heap_size && heap.data[left] > heap.data[i]) {
      largest = left;
    } else {
      largest = i;
    }

    if (right <= heap.heap_size && heap.data[right] > heap.data[i]) {
      largest = right;
    }

    if (largest != i) {
      T temp = heap.data[i];
      heap.data[i] = heap.data[largest];
      heap.data[largest] = temp;
      MaxHeapify(heap, largest);
    }
  }
};
} // namespace heap

#endif // !HEAP_HEAP_HPP
