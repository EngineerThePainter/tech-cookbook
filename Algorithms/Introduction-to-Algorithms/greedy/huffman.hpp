#ifndef GREEDY_HUFFMAN_HPP
#define GREEDY_HUFFMAN_HPP

#include <memory>
#include <vector>

namespace greedy
{

struct Node {
  Node(unsigned int freq, const char v = '0') : freq(freq), val(v) {}
  unsigned int freq;
  char val;
  std::shared_ptr<Node> left = nullptr;
  std::shared_ptr<Node> right = nullptr;
  Node* parent = nullptr;
  std::vector<unsigned int> code;
};

std::shared_ptr<Node> Huffman(std::vector<Node>& starting_nodes);

void TreeWalk(std::shared_ptr<Node> node);
void SetValues(std::shared_ptr<Node> node);
void SetValues(std::shared_ptr<Node> node, const std::vector<unsigned int> val);
}

#endif