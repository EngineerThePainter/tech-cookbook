#include "rb_tree.hpp"

#include <iostream>

namespace data_structures
{
std::shared_ptr<RBNode> RBTree::search(const int key) { return search(root_, key); }

void RBTree::inorderTreeWalk() { inorderTreeWalk(root_); }

void RBTree::inorderTreeWalk(std::shared_ptr<RBNode> node)
{
  if (node != nullptr) {
    inorderTreeWalk(node->left_);
    std::cout << node->key_ << " : " << node->data_ << " : " << (node->color_ == NodeColor::BLACK ? "B" : "R")
              << std::endl;
    inorderTreeWalk(node->right_);
  }
}

std::shared_ptr<RBNode> RBTree::minimum(std::shared_ptr<RBNode> node)
{
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

std::shared_ptr<RBNode> RBTree::successor(std::shared_ptr<RBNode> node)
{
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

void RBTree::leftRotate(std::shared_ptr<RBNode> node)
{
  auto switch_node = node->right_;
  node->right_ = switch_node->left_;
  if (switch_node->left_ != nullptr) {
    switch_node->left_->parent_ = node.get();
  }
  switch_node->parent_ = node->parent_;
  if (node->parent_ == nullptr) {
    root_ = switch_node;
  } else if (node == node->parent_->left_) {
    node->parent_->left_ = switch_node;
  } else {
    node->parent_->right_ = switch_node;
  }
  node->left_ = node;
  node->parent_ = switch_node.get();
}

void RBTree::rightRotate(std::shared_ptr<RBNode> node)
{
  auto switch_node = node->left_;
  node->left_ = switch_node->right_;
  if (switch_node->right_ != nullptr) {
    switch_node->right_->parent_ = node.get();
  }
  switch_node->parent_ = node->parent_;
  if (node->parent_ == nullptr) {
    root_ = switch_node;
    // Does these two conditions can remain as they are?
  } else if (node == node->parent_->right_) {
    node->parent_->right_ = switch_node;
  } else {
    node->parent_->left_ = switch_node;
  }
  node->right_ = node;
  node->parent_ = switch_node.get();
}

std::shared_ptr<RBNode> RBTree::search(std::shared_ptr<RBNode> node, const int key)
{
  if (node == nullptr || key == node->key_) {
    return node;
  }
  if (key < node->key_) {
    return search(node->left_, key);
  } else {
    return search(node->right_, key);
  }
}

void RBTree::insert(const int key, const int data)
{
  std::cout << "insert\n";
  std::shared_ptr<RBNode> z = std::make_shared<RBNode>(key, data);
  std::shared_ptr<RBNode> y = nullptr;
  std::shared_ptr<RBNode> x = root_;
  while (x != nullptr) {
    y = x;
    if (z->key_ < x->key_) {
      x = x->left_;
    } else {
      x = x->right_;
    }
  }
  z->parent_ = y.get();
  if (y == nullptr) {
    root_ = z;
  } else if (z->key_ < y->key_) {
    y->left_ = z;
  } else {
    y->right_ = z;
  }
  z->left_ = nullptr;
  z->right_ = nullptr;
  z->color_ = NodeColor::RED;
  insertFixup(z);
}

void RBTree::insertFixup(std::shared_ptr<RBNode> node)
{
  std::cout << "insert fixup\n";
  while (node->parent_ && node->parent_->color_ == NodeColor::RED) {
    if (node->parent_ == node->parent_->parent_->left_.get()) {
      auto y = node->parent_->parent_->right_;
      if (y->color_ == NodeColor::RED) {
        node->parent_->color_ = NodeColor::BLACK;
        y->color_ = NodeColor::BLACK;
        node->parent_->parent_->color_ = NodeColor::RED;
        node = std::shared_ptr<RBNode>(node->parent_->parent_);
      } else if (node == node->parent_->right_) {
        node = std::shared_ptr<RBNode>(node->parent_);
        leftRotate(node);
        node->parent_->color_ = NodeColor::BLACK;
        node->parent_->parent_->color_ = NodeColor::RED;
        rightRotate(std::shared_ptr<RBNode>(node->parent_->parent_));
      }
    } else {
      auto y = node->parent_->parent_->left_;
      if (y->color_ == NodeColor::RED) {
        node->parent_->color_ = NodeColor::BLACK;
        y->color_ = NodeColor::BLACK;
        node->parent_->parent_->color_ = NodeColor::RED;
        node = std::shared_ptr<RBNode>(node->parent_->parent_);
      } else if (node == node->parent_->right_) {
        node = std::shared_ptr<RBNode>(node->parent_);
        leftRotate(node);
        node->parent_->color_ = NodeColor::BLACK;
        node->parent_->parent_->color_ = NodeColor::RED;
        rightRotate(std::shared_ptr<RBNode>(node->parent_->parent_));
      }
    }
  }
  root_->color_ = NodeColor::BLACK;
}

} // namespace data_structures
