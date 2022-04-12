#ifndef DATA_STRUCTURES_BST_HPP
#define DATA_STRUCTURES_BST_HPP

#include <memory>

namespace data_structures
{
struct TreeElem {
  TreeElem(const int key, const int data) : key(key), data_(data) {}
  ~TreeElem()
  {
    if (left) {
      delete left;
    }
    if (right) {
      delete right;
    }
  }
  const int key;
  const int data_;
  TreeElem* left = nullptr;
  TreeElem* right = nullptr;
  TreeElem* parent = nullptr;
};

class BST
{
public:
  TreeElem* search(const int key);
  TreeElem* searchIteratively(const int key);
  void insert(const int key, const int data);
  void remove(TreeElem* elem);
  void inorderTreeWalk();
  static TreeElem* minimum(TreeElem* node);
  static TreeElem* maximum(TreeElem* node);
  TreeElem* successor(TreeElem* node);

private:
  void inorderTreeWalk(TreeElem* node);
  void transplant(TreeElem* toRemove, TreeElem* toPut);
  TreeElem* search(TreeElem* elem, const int key);
  std::unique_ptr<TreeElem> root_ = nullptr;
};
} // namespace data_structures

#endif
