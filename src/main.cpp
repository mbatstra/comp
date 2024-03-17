#include <iostream>

#include "defs.h"
#include "comp.h"

int main() {
  // get vector of bytes
  byte_vec_t buf;
  read_bytes("data/abcd.txt", buf);

  // construct tree
  pqueue_t nodes;
  init_tree(buf, nodes);
  construct_tree(nodes);

  // all info should now be in the top node
  node_ptr_t tree = nodes.top();
  nodes.pop();

  std::vector<bool> bits;
  serialize_tree(tree.get(), bits);
  std::cout << bits.size() << std::endl;

  // std::bitset<8> bits = 0xff;
  // std::cout << bits << std::endl;

  return 0;
}
