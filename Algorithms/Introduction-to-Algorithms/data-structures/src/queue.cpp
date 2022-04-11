#include "queue.hpp"

#include <iostream>

namespace data_structures
{
Queue::Queue(int size) : data_(std::make_unique<int[]>(size)), size_(size), head_(0), tail_(0) {}

int Queue::dequeue()
{
  int x = data_[head_];
  if (head_ == size_ - 1) {
    head_ = 0;
  } else {
    head_ += 1;
  }
  return x;
}

void Queue::enqueue(int x)
{
  data_[tail_] = x;
  if (tail_ == size_ - 1) {
    tail_ = 0;
  } else {
    tail_ += 1;
  }
}
void Queue::printQueue()
{
  for (int i = 0; i < size_; ++i) {
    std::cout << data_[i] << ", ";
  }
  std::cout << std::endl;
}
} // namespace data_structures