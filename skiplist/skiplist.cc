#include "skiplist.h"
#include <optional>

Skiplist::Skiplist(int max_level) {

  max_level = max_level;

  // Initialize the sentinel nodes
  START = new SkiplistNode(max_level, "", "");
  END = new SkiplistNode(max_level, "", "");
  // Connect the start and end nodes
  for (int i = 0; i < max_level; i++) {
    START->next[i] = END;
  }
}

std::optional<std::string> Skiplist::Search(std::string Key) {
  return std::nullopt;
}

std::optional<std::string> Skiplist::Insert(std::string Key,
                                            std::string Value) {
  // Construct a new node
  // Find the right place to insert it into
  // maintain the update vector
  // Insert the node
  // Update all the pointers in the reachability chain to reach this node
  return std::nullopt;
}
