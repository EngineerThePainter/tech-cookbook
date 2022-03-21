#ifndef HEAP_HEAP_HPP
#define HEAP_HEAP_HPP

#include <iostream>
#include <vector>

namespace heap
{
inline int Parent(const int i) { return i / 2; }
inline int Left(const int i) { return i == 0 ? 1 : (i * 2) + 1; }
inline int Right(const int i) { return Left(i) + 1; }

template <typename T> class Heap
{
public:
  Heap(const std::vector<T> data) : data_(std::move(data)) {}

  std::vector<T>& Data() { return data_; }
  int& HeapSize() { return heap_size; }
  void PrintHeap()
  {
    for (const auto& d : data_) {
      std::cout << d << std::endl;
    }
  }

  void IncrementAssignements() { nb_assignements++; }
  void IncrementComparisons() { nb_comparisons++; }

  long long Assignements() const { return nb_assignements; }
  long long Comparisons() const { return nb_comparisons; }
  void ResetStats()
  {
    nb_assignements = 0;
    nb_comparisons = 0;
  }

private:
  std::vector<T> data_;
  int heap_size{};
  long long nb_assignements{};
  long long nb_comparisons{};
};

template <typename T> void MaxHeapify(Heap<T>& heap, const int i)
{
  const int left_index = Left(i);
  const int right_index = Right(i);
  int largest = -1;

  heap.IncrementComparisons();
  if (left_index < heap.HeapSize() && heap.Data()[left_index] > heap.Data()[i]) {
    largest = left_index;
  } else {
    largest = i;
  }

  heap.IncrementComparisons();
  if (right_index < heap.HeapSize() && heap.Data()[right_index] > heap.Data()[largest]) {
    largest = right_index;
  }

  if (largest != i) {
    T temp = heap.Data()[i];
    heap.IncrementAssignements();
    heap.Data()[i] = heap.Data()[largest];
    heap.IncrementAssignements();
    heap.Data()[largest] = temp;
    MaxHeapify(heap, largest);
  }
}

template <typename T> void BuildMaxHeap(Heap<T>& heap)
{
  heap.ResetStats();
  heap.HeapSize() = heap.Data().size();
  for (int i = heap.Data().size() - 1; i >= 0; --i) {
    MaxHeapify(heap, i);
  }
}

} // namespace heap

#endif // !HEAP_HEAP_HPP
