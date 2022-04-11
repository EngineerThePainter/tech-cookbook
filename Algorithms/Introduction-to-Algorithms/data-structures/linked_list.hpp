#ifndef DATA_STRUCTURES_LINKED_LIST_HPP
#define DATA_STRUCTURES_LINKED_LIST_HPP

#include <memory>

namespace data_structures
{
struct ListElem {
  ListElem(const int key, const int data) : key(key), data_(data) {}
  const int key;
  const int data_;
  std::shared_ptr<ListElem> next = nullptr;
  std::shared_ptr<ListElem> prev = nullptr;
};

class LinkedList
{
public:
  std::shared_ptr<ListElem> search(const int key);
  void insert(ListElem&& elem);
  void remove (std::shared_ptr<ListElem> elem);
  void printList();

private:
  std::shared_ptr<ListElem> head_;
};
} // namespace data_structures

#endif
