#ifndef DATA_STRUCTURES_RBT_HPP
#define DATA_STRUCTURES_RBT_HPP

#include <memory>

namespace data_structures
{
enum class NodeColor { RED = 0, BLACK };

struct RBNode {
  RBNode(const int key, const int data)
      : key_(key), data_(data), left_(nullptr), right_(nullptr), parent_(nullptr), color_(NodeColor::BLACK)
  {
  }
  ~RBNode()
  {
    if (left_ != nullptr) {
      delete left_;
    }
    if (right_ != nullptr) {
      delete right_;
    }
  }
  const int key_;
  const int data_;
  RBNode* left_;
  RBNode* right_;
  RBNode* parent_;
  NodeColor color_;
};

class RBTree
{
public:
  ~RBTree();
  RBNode* search(const int key);
  void inorderTreeWalk();
  static RBNode* minimum(RBNode* node);
  static RBNode* maximum(RBNode* node);
  RBNode* successor(RBNode* node);
  void leftRotate(RBNode* node);
  void rightRotate(RBNode* node);
  void insert(const int key, const int data);
  void transplant(RBNode* toRemove, RBNode* toPut, RBNode* toPutParent);
  void remove(RBNode* z);

private:
  void inorderTreeWalk(RBNode* node);
  void insertFixup(RBNode* node);
  void removeFixup(RBNode* node);
  RBNode* search(RBNode* elem, const int key);

  RBNode* root_ = nullptr;
};

} // namespace data_structures

#endif
