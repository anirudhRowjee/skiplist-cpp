#include "sl/skiplist.h"

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

std::pair<std::string, SkiplistError>
Skiplist::Insert(const std::string &key, const std::string &value) {
  // Construct a new node
  // Find the right place to insert it into
  // maintain the update vector
  // Insert the node
  // Update all the pointers in the reachability chain to reach this node
  return std::make_pair("",
                        SkiplistError(SkiplistError::ErrorVariant::BAD_ACCESS));
}

std::pair<std::string, SkiplistError> Skiplist::Delete(std::string Key) {
  return std::make_pair("",
                        SkiplistError(SkiplistError::ErrorVariant::BAD_ACCESS));
}

Skiplist::~Skiplist() {
  // Get all keys via range scan
  // Delete all keys one by one to avoid reference counting hell
  // std::cout << "Destructing Skiplist" << std::endl;
}
