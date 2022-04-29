#include "rb_tree.hpp"

#include <iostream>
#include <string>

namespace data_structures
{

RBTree::~RBTree() { delete root_; }

RBNode* RBTree::search(const int key) { return search(root_, key); }

void RBTree::inorderTreeWalk() { inorderTreeWalk(root_); }

void RBTree::inorderTreeWalk(RBNode* node)
{
  if (node != nullptr) {
    inorderTreeWalk(node->left_);
    std::string color = node->color_ == NodeColor::BLACK ? "B" : "R";
    std::cout << node->key_ << color;
    if (node->left_ != nullptr) {
      std::cout << " : L" << node->left_->key_;
    }
    if (node->right_ != nullptr) {
      std::cout << " : R" << node->right_->key_;
    }
    if (node->parent_ != nullptr) {
      std::cout << " : P" << node->parent_->key_;
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

void RBTree::leftRotate(RBNode* x)
{
  if (x->right_ == nullptr) {
    return;
  }
  auto y = x->right_;
  x->right_ = y->left_;
  if (y->left_ != nullptr) {
    y->left_->parent_ = x;
  }
  y->parent_ = x->parent_;
  if (x->parent_ == nullptr) {
    root_ = y;
  } else if (x == x->parent_->left_) {
    x->parent_->left_ = y;
  } else {
    x->parent_->right_ = y;
  }
  y->left_ = x;
  x->parent_ = y;
}

void RBTree::rightRotate(RBNode* y)
{
  if (y->left_ == nullptr) {
    return;
  }
  auto x = y->left_;
  y->left_ = x->right_;
  if (x->right_ != nullptr) {
    x->right_->parent_ = y;
  }
  x->parent_ = y->parent_;
  if (y->parent_ == nullptr) {
    root_ = x;
    // Does these two conditions can remain as they are?
  } else if (y == y->parent_->right_) {
    y->parent_->right_ = x;
  } else {
    y->parent_->left_ = x;
  }
  x->right_ = y;
  y->parent_ = x;
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

void RBTree::insertFixup(RBNode* z)
{
  while (z->parent_ && z->parent_->color_ == NodeColor::RED) {
    if (z->parent_ == z->parent_->parent_->left_) {
      auto y = z->parent_->parent_->right_;
      if (y != nullptr && y->color_ == NodeColor::RED) {
        z->parent_->color_ = NodeColor::BLACK;
        y->color_ = NodeColor::BLACK;
        z->parent_->parent_->color_ = NodeColor::RED;
        z = z->parent_->parent_;
      } else {
        if (z == z->parent_->right_) {
          z = z->parent_;
          leftRotate(z);
        }
        z->parent_->color_ = NodeColor::BLACK;
        z->parent_->parent_->color_ = NodeColor::RED;
        rightRotate(z->parent_->parent_);
      }
    } else {
      auto y = z->parent_->parent_->left_;

      if (y != nullptr && y->color_ == NodeColor::RED) {
        z->parent_->color_ = NodeColor::BLACK;
        y->color_ = NodeColor::BLACK;
        z->parent_->parent_->color_ = NodeColor::RED;
        z = z->parent_->parent_;
      } else {
        if (z == z->parent_->left_) {
          z = z->parent_;
          leftRotate(z);
        }
        z->parent_->color_ = NodeColor::BLACK;
        z->parent_->parent_->color_ = NodeColor::RED;
        rightRotate(z->parent_->parent_);
      }
    }
  }
  root_->color_ = NodeColor::BLACK;
}

void RBTree::transplant(RBNode* u, RBNode* v, RBNode* parent_v)
{
  if (u->parent_ == nullptr) {
    root_ = v;
  } else if (u == u->parent_->left_) {
    u->parent_->left_ = v;
  } else {
    u->parent_->right_ = v;
  }
  if (v) {
    v->parent_ = u->parent_;
  } else {
    parent_v = u->parent_;
  }
}

void RBTree::remove(RBNode* z)
{
  RBNode* y = z;
  RBNode* x = nullptr;
  NodeColor original_color = y->color_;
  if (z->left_ == nullptr) {
    x = z->right_;
    transplant(z, z->right_, z);
  } else if (z->right_ == nullptr) {
    x = z->left_;
    transplant(z, z->left_, z);
  } else {
    y = minimum(z->right_);
    original_color = y->color_;
    x = y->right_;
    if (y->parent_ == z) {
      x->parent_ = y;
    } else {
      transplant(y, y->right_, y);
      y->right_ = z->right_;
      y->right_->parent_ = y;
    }
    transplant(z, y, y->parent_);
    y->left_ = z->left_;
    y->left_->parent_ = y;
    y->color_ = z->color_;
  }
  if (original_color == NodeColor::BLACK) {
    removeFixup(x);
  }
}

void RBTree::removeFixup(RBNode* x)
{
  while (x != nullptr && x != root_ && x->color_ == NodeColor::BLACK) {
    if (x == x->parent_->left_) {
      RBNode* w = x->parent_->right_;
      if (w->color_ == NodeColor::RED) {
        w->color_ = NodeColor::BLACK;
        x->parent_->color_ = NodeColor::RED;
        leftRotate(x->parent_);
        w = x->parent_->right_;
      }
      if (w->left_->color_ == NodeColor::BLACK && w->right_->color_ == NodeColor::BLACK) {
        w->color_ = NodeColor::RED;
        x = x->parent_;
      } else {
        if (w->right_->color_ == NodeColor::BLACK) {
          w->left_->color_ = NodeColor::BLACK;
          w->color_ = NodeColor::RED;
          rightRotate(w);
          w = x->parent_->right_;
        }
        w->color_ = x->parent_->color_;
        x->parent_->color_ = NodeColor::BLACK;
        w->right_->color_ = NodeColor::BLACK;
        leftRotate(x->parent_);
        x = root_;
      }
    } else {
      if (x == x->parent_->right_) {
        RBNode* w = x->parent_->left_;
        if (w->color_ == NodeColor::RED) {
          w->color_ = NodeColor::BLACK;
          x->parent_->color_ = NodeColor::RED;
          leftRotate(x->parent_);
          w = x->parent_->left_;
        }
        if (w->right_->color_ == NodeColor::BLACK && w->left_->color_ == NodeColor::BLACK) {
          w->color_ = NodeColor::RED;
          x = x->parent_;
        } else {
          if (w->left_->color_ == NodeColor::BLACK) {
            w->right_->color_ = NodeColor::BLACK;
            w->color_ = NodeColor::RED;
            rightRotate(w);
            w = x->parent_->right_;
          }
          w->color_ = x->parent_->color_;
          x->parent_->color_ = NodeColor::BLACK;
          w->left_->color_ = NodeColor::BLACK;
          leftRotate(x->parent_);
          x = root_;
        }
      }
    }
  }
  if (x) {
    x->color_ = NodeColor::BLACK;
  }
}

} // namespace data_structures
