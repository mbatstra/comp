#include <criterion/criterion.h>
#include <criterion/logging.h>

using criterion::logging::warn;

#include "src/comp.h"
#include "src/defs.h"

static void db_pttree(const std::string& prefix, node_ptr_t node, bool is_left) {
  if (!is_leaf_node(node.get())) {
    internal_node_t internal = *(static_cast<internal_node_t*>(node.get()));

    warn << prefix;
    warn << (is_left ? "├──" : "└──");
    warn << node->weight << std::endl;

    db_pttree(prefix + (is_left ?  "│   " : "    "), internal.left, true);
    db_pttree(prefix + (is_left ?  "│   " : "    "), internal.right, false);
  }
  else {
    leaf_node_t leaf = *(static_cast<leaf_node_t*>(node.get()));
    warn << prefix;
    warn << (is_left ? "├──" : "└──");
    warn << (char) leaf.byte << std::endl;
  }
}

static void db_pttree(node_ptr_t node) {
  db_pttree("", node, false);
}

Test(comp, SerializeTree) {
  byte_vec_t buf;
  read_bytes("data/abc.txt", buf);

  pqueue_t nodes;
  init_tree(buf, nodes);
  construct_tree(nodes);

  node_ptr_t tree = nodes.top();
  nodes.pop();

  std::vector<bool> bits;
  serialize_tree(tree.get(), bits);

  db_pttree(tree);
  for (const auto &bit : bits) {
    warn << bit;
  }
  warn << "\n" << bits.size();
  warn << std::endl;
}
