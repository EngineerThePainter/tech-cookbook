#include "rb_tree.hpp"

#include <iostream>

namespace data_structures
{

RBTree::~RBTree() { delete root_; }

RBNode* RBTree::search(const int key) { return search(root_, key); }

void RBTree::inorderTreeWalk() { inorderTreeWalk(root_); }

void RBTree::inorderTreeWalk(RBNode* node)
{
  if (node != nullptr) {
    inorderTreeWalk(node->left_);
    std::cout << node->key_ << " : " << node->data_ << " : " << (node->color_ == NodeColor::BLACK ? "B" : "R");
    if (node->parent_ != nullptr) {
      std::cout << node->parent_->key_;
    }
    std::cout << std::endl;
    inorderTreeWalk(node->right_);
  }
}

RBNode* RBTree::minimum(RBNode* node)
{
  while (node->left_ != nullptr) {
    node = node->left_;
  }
  return node;
}

RBNode* RBTree::maximum(RBNode* node)
{
  while (node->right_ != nullptr) {
    node = node->right_;
  }
  return node;
}

RBNode* RBTree::successor(RBNode* node)
{
  if (node->right_ != nullptr) {
    return minimum(node->right_);
  }
  RBNode* y = node->parent_;
  while (y != nullptr && node != y->right_) {
    node = y;
    y = y->parent_;
  }
  return y;
}

void RBTree::leftRotate(RBNode* node)
{
  auto switch_node = node->right_;
  node->right_ = switch_node->left_;
  if (switch_node->left_ != nullptr) {
    switch_node->left_->parent_ = node;
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
  node->parent_ = switch_node;
}

void RBTree::rightRotate(RBNode* node)
{
  auto switch_node = node->left_;
  node->left_ = switch_node->right_;
  if (switch_node->right_ != nullptr) {
    switch_node->right_->parent_ = node;
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
  node->parent_ = switch_node;
}

RBNode* RBTree::search(RBNode* node, const int key)
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
  RBNode* z = new RBNode(key, data);
  RBNode* y = nullptr;
  RBNode* x = root_;
  while (x != nullptr) {
    y = x;
    if (z->key_ < x->key_) {
      x = x->left_;
    } else {
      x = x->right_;
    }
  }
  z->parent_ = y;
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

void RBTree::insertFixup(RBNode* node)
{
  std::cout << "insert fixup\n";
  while (node->parent_ && node->parent_->color_ == NodeColor::RED) {
    if (node->parent_ == node->parent_->parent_->left_) {
      auto y = node->parent_->parent_->right_;
      if (y->color_ == NodeColor::RED) {
        node->parent_->color_ = NodeColor::BLACK;
        y->color_ = NodeColor::BLACK;
        node->parent_->parent_->color_ = NodeColor::RED;
        node = node->parent_->parent_;
      } else {
        if (node == node->parent_->right_) {
          node = node->parent_;
          leftRotate(node);
        }
        node->parent_->color_ = NodeColor::BLACK;
        node->parent_->parent_->color_ = NodeColor::RED;
        rightRotate(node->parent_->parent_);
      }
    } else {
      auto y = node->parent_->parent_->left_;
      if (y->color_ == NodeColor::RED) {
        node->parent_->color_ = NodeColor::BLACK;
        y->color_ = NodeColor::BLACK;
        node->parent_->parent_->color_ = NodeColor::RED;
        node = node->parent_->parent_;
      } else {
        if (node == node->parent_->right_) {
          node = node->parent_;
          leftRotate(node);
        }
        node->parent_->color_ = NodeColor::BLACK;
        node->parent_->parent_->color_ = NodeColor::RED;
        rightRotate(node->parent_->parent_);
      }
    }
  }
  root_->color_ = NodeColor::BLACK;
}

} // namespace data_structures
