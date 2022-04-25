#ifndef DATA_STRUCTURES_RBT_HPP
#define DATA_STRUCTURES_RBT_HPP

#include <memory>

namespace data_structures
{
enum class NodeColor { RED = 0, BLACK };

struct RBNode {
  RBNode(const int key, const int data) : key_(key), data_(data) {}
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
  RBNode* left_ = nullptr;
  RBNode* right_ = nullptr;
  RBNode* parent_ = nullptr;
  NodeColor color_ = NodeColor::BLACK;
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

private:
  void inorderTreeWalk(RBNode* node);
  void insertFixup(RBNode* node);
  RBNode* search(RBNode* elem, const int key);

  RBNode* root_ = nullptr;
};

} // namespace data_structures

#endif
