#include "bst.hpp"

#include "iostream"

namespace data_structures
{
TreeElem* BST::search(const int key) { return search(root_.get(), key); }

TreeElem* BST::searchIteratively(const int key)
{
  auto node = root_.get();
  while (node != nullptr && key != node->key) {
    if (key < node->key) {
      node = node->left;
    } else {
      node = node->right;
    }
  }
  return node;
}

void BST::insert(const int key, const int data)
{
  TreeElem* elem = new TreeElem(key, data);
  TreeElem* y = nullptr;
  TreeElem* x = root_.get();
  while (x != nullptr) {
    y = x;
    if (elem->key < x->key) {
      x = x->left;
    } else {
      x = x->right;
    }
  }
  elem->parent = y;
  if (y == nullptr) {
    root_ = std::unique_ptr<TreeElem>(std::move(elem));
  } else if (elem->key < y->key) {
    y->left = elem;
  } else {
    y->right = elem;
  }
}

void BST::remove(TreeElem* elem)
{
  if (elem->left == nullptr) {
    transplant(elem, elem->right);
  } else if (elem->right == nullptr) {
    transplant(elem, elem->left);
  } else {
    TreeElem* y = minimum(elem->right);
    if (y->parent != elem) {
      transplant(y, y->right);
      y->right = elem->right;
      y->right->parent = y;
    }
    transplant(elem, y);
    y->left = elem->left;
    y->left->parent = y;
  }
}

void BST::inorderTreeWalk() { inorderTreeWalk(root_.get()); }

void BST::inorderTreeWalk(TreeElem* node)
{
  if (node != nullptr) {
    inorderTreeWalk(node->left);
    std::cout << node->key << " : " << node->data_ << std::endl;
    inorderTreeWalk(node->right);
  }
}

TreeElem* BST::minimum(TreeElem* node)
{
  while (node->left != nullptr) {
    node = node->left;
  }
  return node;
}

TreeElem* BST::maximum(TreeElem* node)
{
  while (node->right != nullptr) {
    node = node->right;
  }
  return node;
}

TreeElem* BST::successor(TreeElem* node)
{
  if (node->right != nullptr) {
    return minimum(node->right);
  }
  TreeElem* y = node->parent;
  while (y != nullptr && node != y->right) {
    node = y;
    y = y->parent;
  }
  return y;
}

void BST::transplant(TreeElem* toRemove, TreeElem* toPut)
{
  if (toRemove->parent == nullptr) {
    root_.reset(toPut);
  } else if (toRemove == toRemove->parent->left) {
    toRemove->parent->left = toPut;
  } else {
    toRemove->parent->right = toPut;
  }
  if (toPut != nullptr) {
    toPut->parent = toRemove->parent;
  }
}

TreeElem* BST::search(TreeElem* elem, const int key)
{
  if (elem == nullptr || key == elem->key) {
    return elem;
  }
  if (key < elem->key) {
    return search(elem->left, key);
  } else {
    return search(elem->right, key);
  }
}

} // namespace data_structures