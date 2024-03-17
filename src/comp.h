#ifndef COMP_H
#define COMP_H
#include "defs.h"

// read file into vector as binary data
void read_bytes(const std::string &path, byte_vec_t& buf);

// serialize tree so it can be written to file header
void serialize_tree(node_t* tree, std::vector<bool>& bits);

// create a leaf node per symbol and put them in a priority queue
void init_tree(const byte_vec_t& bytes, pqueue_t& nodes);

// construct the full huffman tree; make sure to call init_queue first
void construct_tree(pqueue_t& nodes);

// remove at most first 8 bits und return them in a byte
unsigned char extract_and_remove_byte(byte_vec_t& bytes);

inline bool is_leaf_node(node_t* node) {
  return dynamic_cast<leaf_node_t*>(node) != nullptr;
}

#endif // !COMP_H
