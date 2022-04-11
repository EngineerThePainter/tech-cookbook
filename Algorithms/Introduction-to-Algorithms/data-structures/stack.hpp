#ifndef DATA_STRUCTURES_STACK_HPP
#define DATA_STRUCTURES_STACK_HPP

#include <memory>

namespace data_structures
{
class Stack
{
public:
  explicit Stack(int size);
  bool empty();
  int pop();
  void push(int x);
  void printStack();

private:
  std::unique_ptr<int[]> data_;
  const int size_;
  int top_;
};
} // namespace data_structures

#endif