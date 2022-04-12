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
void LinkedList::insert(const int key, const int data)
{
  auto item = std::make_shared<ListElem>(key, data);

  if (head_ != nullptr) {
    head_->prev = item.get();
  }
  item->next = std::move(head_);
  head_ = std::move(item);
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
