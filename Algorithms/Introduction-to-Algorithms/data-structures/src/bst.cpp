#include "bst.hpp"

#include "iostream"

namespace data_structures
{
std::shared_ptr<TreeElem> BST::search(const int key) { return search(root_, key); }

std::shared_ptr<TreeElem> BST::searchIteratively(const int key)
{
  auto node = root_;
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
  std::shared_ptr<TreeElem> elem = std::make_shared<TreeElem>(key, data);
  std::shared_ptr<TreeElem> y = nullptr;
  std::shared_ptr<TreeElem> x = root_;
  while (x != nullptr) {
    y = x;
    if (elem->key < x->key) {
      x = x->left;
    } else {
      x = x->right;
    }
  }
  elem->parent = y.get();
  if (y == nullptr) {
    root_ = std::move(elem);
  } else if (elem->key < y->key) {
    y->left = std::move(elem);
  } else {
    y->right = std::move(elem);
  }
}

void BST::remove(std::shared_ptr<TreeElem> elem)
{
  if (elem->left == nullptr) {
    transplant(elem, elem->right);
  } else if (elem->right == nullptr) {
    transplant(elem, elem->left);
  } else {
    std::shared_ptr<TreeElem> y = minimum(elem->right);
    if (y->parent != elem.get()) {
      transplant(y, y->right);
      y->right = std::move(elem->right);
      y->right->parent = y.get();
    }
    transplant(elem, y);
    y->left = std::move(elem->left);
    y->left->parent = y.get();
  }
  elem.reset();
}

void BST::inorderTreeWalk() { inorderTreeWalk(root_); }

void BST::inorderTreeWalk(std::shared_ptr<TreeElem> node)
{
  if (node != nullptr) {
    inorderTreeWalk(node->left);
    std::cout << node->key << " : " << node->data_ << std::endl;
    inorderTreeWalk(node->right);
  }
}

std::shared_ptr<TreeElem> BST::minimum(std::shared_ptr<TreeElem> node)
{
  while (node->left != nullptr) {
    node = node->left;
  }
  return node;
}

std::shared_ptr<TreeElem> BST::maximum(std::shared_ptr<TreeElem> node)
{
  while (node->right != nullptr) {
    node = node->right;
  }
  return node;
}

std::shared_ptr<TreeElem> BST::successor(std::shared_ptr<TreeElem> node)
{
  if (node->right != nullptr) {
    return minimum(node->right);
  }
  std::shared_ptr<TreeElem> y = std::shared_ptr<TreeElem>(node->parent);
  while (y != nullptr && node != y->right) {
    node = y;
    y = std::shared_ptr<TreeElem>(y->parent);
  }
  return y;
}

void BST::transplant(std::shared_ptr<TreeElem> toRemove, std::shared_ptr<TreeElem> toPut)
{
  if (toRemove->parent == nullptr) {
    root_ = std::move(toPut);
  } else if (toRemove == toRemove->parent->left) {
    toRemove->parent->left = std::move(toPut);
  } else {
    toRemove->parent->right = std::move(toPut);
  }
  if (toPut != nullptr) {
    toPut->parent = toRemove->parent;
  }
}

std::shared_ptr<TreeElem> BST::search(std::shared_ptr<TreeElem> elem, const int key)
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
