#include "stack.hpp"

#include <exception>
#include <iostream>

namespace data_structures
{
Stack::Stack(const int size) : data_(std::make_unique<int[]>(size)), size_(size), top_(0) {}

bool Stack::empty()
{
  if (top_ == 0) {
    return true;
  }
  return false;
}

int Stack::pop()
{
  if (empty()) {
    throw std::length_error("Stack is empty");
  } else {
    top_ -= 1;
    return data_[top_];
  }
  
}

void Stack::push(int x)
{
  if (top_ >= size_) {
    throw std::length_error("Stack is full");
  }
  top_ += 1;
  data_[top_-1] = x;
}

void Stack::printStack()
{
  for (int i = 0; i < size_; ++i) {
    std::cout << data_[i] << ", ";
  }
  std::cout << std::endl;
}
} // namespace data_structures