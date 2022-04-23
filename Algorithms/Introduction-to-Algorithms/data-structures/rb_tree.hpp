#ifndef DATA_STRUCTURES_RBT_HPP
#define DATA_STRUCTURES_RBT_HPP

#include <memory>

namespace data_structures
{
enum class NodeColor { RED = 0, BLACK };

struct RBNode {
  RBNode(const int key, const int data) : key_(key), data_(data) {}
  const int key_;
  const int data_;
  std::shared_ptr<RBNode> left_ = nullptr;
  std::shared_ptr<RBNode> right_ = nullptr;
  RBNode* parent_ = nullptr;
  NodeColor color_ = NodeColor::BLACK;
};

class RBTree
{
public:
  std::shared_ptr<RBNode> search(const int key);
  void inorderTreeWalk();
  static std::shared_ptr<RBNode> minimum(std::shared_ptr<RBNode> node);
  static std::shared_ptr<RBNode> maximum(std::shared_ptr<RBNode> node);
  std::shared_ptr<RBNode> successor(std::shared_ptr<RBNode> node);
  void leftRotate(std::shared_ptr<RBNode> node);
  void rightRotate(std::shared_ptr<RBNode> node);

private:
  void inorderTreeWalk(std::shared_ptr<RBNode> node);
  std::shared_ptr<RBNode> search(std::shared_ptr<RBNode> elem, const int key);

  std::shared_ptr<RBNode> root_ = nullptr;
};

} // namespace data_structures

#endif
