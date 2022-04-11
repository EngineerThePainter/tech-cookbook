#ifndef DATA_STRUCTURES_QUEUE_HPP
#define DATA_STRUCTURES_QUEUE_HPP

#include <memory>

namespace data_structures
{
class Queue
{
public:
  explicit Queue(int size);
  int dequeue();
  void enqueue(int x);
  void printQueue();

private:
  std::unique_ptr<int[]> data_;
  const int size_;
  int head_;
  int tail_;
};
} // namespace data_structures

#endif