#include <fstream>
#include <iterator>
#include <stdexcept>
#include <string>

#include "defs.h"
#include "comp.h"

void read_bytes(const std::string &path, byte_vec_t& buf) {
  std::ifstream input(path);
  if (!input.is_open()) {
    throw std::runtime_error("failed to open file for reading");
  }
  std::copy(
    std::istreambuf_iterator<char>(input),
    std::istreambuf_iterator<char>(),
    std::back_inserter(buf));
  input.close();
}

void serialize_tree(node_t* tree, std::vector<bool>& bits) {
  // write a 0 and continue down the tree
  if (!is_leaf_node(tree)) {
    internal_node_t internal = *(static_cast<internal_node_t*>(tree));
    bits.push_back(false);
    serialize_tree(internal.left.get(), bits);
    serialize_tree(internal.right.get(), bits);
  }
  // final node; write byte value
  else {
    leaf_node_t leaf = *(static_cast<leaf_node_t*>(tree));
    bits.push_back(true);
    unsigned char c = leaf.byte;
    for (int i = 0; i < 8; i++) {
      bits.push_back(c & 0x1);
      c >>= 1;
    }
  }
}

void init_tree(const byte_vec_t& bytes, pqueue_t& nodes) {
  // count occurences per byte
  unsigned char weights[0xff]{};
  for (const auto &byte : bytes) {
    weights[byte]++;
  }
  // create leaf node for each nonzero weight
  unsigned char byte = 0;
  for (const auto &weight : weights) {
    if (weight) {
      nodes.push(std::make_shared<leaf_node_t>(byte, weight));
    }
    byte++;
  }
}

void construct_tree(pqueue_t& nodes) {
  // pair nodes until top node contains the entire tree
  while (nodes.size() > 1) {
    node_ptr_t lhs = std::move(nodes.top());
    nodes.pop();
    node_ptr_t rhs = std::move(nodes.top());
    nodes.pop();
    node_ptr_t internal = std::make_shared<internal_node_t>(lhs, rhs);
    nodes.push(internal);
  }
}

unsigned char extract_and_remove_byte(byte_vec_t& bytes) {
  unsigned char c = 0x0;
  for (int i = 0; i < 8 || i < bytes.size(); i++) {
    c |= bytes[i];
  }
  auto it = bytes.begin();
  bytes.erase(it, it + 8);
  return c;
}
