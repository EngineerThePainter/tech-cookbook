#ifndef DATA_STRUCTURES_BST_HPP
#define DATA_STRUCTURES_BST_HPP

#include <memory>

namespace data_structures
{
struct TreeElem {
  TreeElem(const int key, const int data) : key(key), data_(data) {}
  const int key;
  const int data_;
  std::shared_ptr<TreeElem> left = nullptr;
  std::shared_ptr<TreeElem> right = nullptr;
  TreeElem* parent = nullptr;
};

class BST
{
public:
  std::shared_ptr<TreeElem> search(const int key);
  std::shared_ptr<TreeElem> searchIteratively(const int key);
  void insert(const int key, const int data);
  void remove(std::shared_ptr<TreeElem> elem);
  void inorderTreeWalk();
  static std::shared_ptr<TreeElem> minimum(std::shared_ptr<TreeElem> node);
  static std::shared_ptr<TreeElem> maximum(std::shared_ptr<TreeElem> node);
  std::shared_ptr<TreeElem> successor(std::shared_ptr<TreeElem> node);

private:
  void inorderTreeWalk(std::shared_ptr<TreeElem> node);
  void transplant(std::shared_ptr<TreeElem> toRemove, std::shared_ptr<TreeElem> toPut);
  std::shared_ptr<TreeElem> search(std::shared_ptr<TreeElem> elem, const int key);
  std::shared_ptr<TreeElem> root_ = nullptr;
};
} // namespace data_structures

#endif
