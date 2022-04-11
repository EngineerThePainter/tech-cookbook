#include "linked_list.hpp"

#include <iostream>

namespace data_structures
{
std::shared_ptr<ListElem> LinkedList::search(const int key)
{
  auto x = head_;
  while (x != nullptr && x->key != key) {
    x = x->next;
  }
  return x;
}
void LinkedList::insert(ListElem&& elem)
{
  auto item = std::make_shared<ListElem>(elem);
  item->next = head_;
  if (head_ != nullptr) {
    head_->prev = item;
  }
  head_ = item;
  item->prev = nullptr;
}

void LinkedList::remove(std::shared_ptr<ListElem> elem)
{
  if (elem->prev != nullptr) {
    elem->prev->next = elem->next;
  } else {
    head_->next = elem->next;
  }
  if (elem->next != nullptr) {
    elem->next->prev = elem->prev;
  }
  elem.reset();
}

void LinkedList::printList()
{
  auto elem = head_;
  while (elem != nullptr) {
    std::cout << elem->data_ << ", ";
    elem = elem->next;
  }
  std::cout << std::endl;
}
} // namespace data_structures
