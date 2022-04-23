#include "rb_tree.hpp"

#include <iostream>

namespace data_structures
{
std::shared_ptr<RBNode> RBTree::search(const int key)
{
  return search(root_, key);
}

void RBTree::inorderTreeWalk() { inorderTreeWalk(root_); }

void RBTree::inorderTreeWalk(std::shared_ptr<RBNode> node)
{
  if (node != nullptr) {
    inorderTreeWalk(node->left_);
    std::cout << node->key_ << " : " << node->data_ << std::endl;
    inorderTreeWalk(node->right_);
  }
}

std::shared_ptr<RBNode> RBTree::minimum(std::shared_ptr<RBNode> node) {
  while (node->left_ != nullptr) {
    node = node->left_;
  }
  return node;
}

std::shared_ptr<RBNode> RBTree::maximum(std::shared_ptr<RBNode> node)
{
  while (node->right_ != nullptr) {
    node = node->right_;
  }
  return node;
}

std::shared_ptr<RBNode> RBTree::successor(std::shared_ptr<RBNode> node) {
  if (node->right_ != nullptr) {
    return minimum(node->right_);
  }
  std::shared_ptr<RBNode> y = std::shared_ptr<RBNode>(node->parent_);
  while (y != nullptr && node != y->right_) {
    node = y;
    y = std::shared_ptr<RBNode>(y->parent_);
  }
  return y;
}

std::shared_ptr<RBNode> RBTree::search(std::shared_ptr<RBNode> node, const int key) {
  if (node == nullptr || key == node->key_) {
    return node;
  }
  if (key < node->key_) {
    return search(node->left_, key);
  } else {
    return search(node->right_, key);
  }
}
}