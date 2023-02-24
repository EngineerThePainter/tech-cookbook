#include "huffman.hpp"

#include <iostream>
#include <queue>

namespace greedy
{
std::shared_ptr<Node> Huffman(std::vector<Node>& starting_nodes)
{
  auto cmp = [](const std::shared_ptr<Node> a, const std::shared_ptr<Node> b) { return a->freq >= b->freq; };

  std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, decltype(cmp)> node_queue(cmp);
  for (auto& node : starting_nodes) {
    node_queue.push(std::make_shared<Node>(node));
  }

  for (int i = 1; i < starting_nodes.size(); ++i) {
    auto x = node_queue.top();
    node_queue.pop();
    auto y = node_queue.top();
    node_queue.pop();
    std::shared_ptr<Node> z = std::make_shared<Node>(x->freq + y->freq);
    z->left = x;
    z->right = y;
    x->parent = z.get();
    y->parent = z.get();
    node_queue.push(z);
  }
  return node_queue.top();
}

void TreeWalk(std::shared_ptr<Node> node)
{
  if (node != nullptr) {
    TreeWalk(node->left);
    if (node->val != '0') {
      std::cout << node->val << ": ";
      for (const auto& c : node->code) {
        std::cout << c;
      }
      std::cout << std::endl;
    }
    TreeWalk(node->right);
  }
}

void SetValues(std::shared_ptr<Node> node)
{
  SetValues(node->left, {0});
  SetValues(node->right, {1});
}

void SetValues(std::shared_ptr<Node> node, const std::vector<unsigned int> val)
{
  if (node != nullptr) {
    node->code = val;
    if (node->val == '0') {
      auto l = val;
      l.push_back(0);
      auto r = val;
      r.push_back(1);
      SetValues(node->left, l);
      SetValues(node->right, r);
    }
  }
}

} // namespace greedy
