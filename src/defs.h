#ifndef DEFS_H
#define DEFS_H
#include <cstddef>
#include <memory>
#include <vector>
#include <queue>

// base node; virtual destructor so we can use dynamic_cast
struct node_t {
  size_t weight;

  bool operator<(const node_t& other) const {
    return weight < other.weight;
  }

  virtual ~node_t() = default;
};

// leaf node; end node with an actual value
struct leaf_node_t : public node_t {
  unsigned char byte;

  leaf_node_t(unsigned char b, size_t w) : byte(b) { weight = w; }
};

using node_ptr_t = std::shared_ptr<node_t>;

// internal node; intermediate nodes with weight but no value
struct internal_node_t : public node_t {
  node_ptr_t left;
  node_ptr_t right;

  internal_node_t(node_ptr_t l, node_ptr_t r)
    : left(*l < *r ? l : r), right(*l < *r ? r : l) {
    weight = l->weight + r->weight;
  }
};

// comparator for priority_queue
struct node_greater_equal {
  bool operator()(node_ptr_t& lhs, node_ptr_t& rhs) {
    return *rhs < *lhs;
  }
};

using pqueue_t = std::priority_queue<node_ptr_t, std::vector<node_ptr_t>, node_greater_equal>;
using byte_vec_t = std::vector<unsigned char>;

#endif // !DEFS_H
