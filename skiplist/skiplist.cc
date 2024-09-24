#include "sl/skiplist.h"

#include <cstdlib>
#include <iostream>
#include <optional>
#include <random>

Skiplist::Skiplist(int max_level) : max_level(max_level) {

  // TODO need to see if this suffices
  p = 0.5;
  rng = std::mt19937(std::time(nullptr)); // fixed seed as of now
  distribution = std::uniform_real_distribution<double>(0.0, 1.0);

  // Initialize the sentinel nodes
  // Need to figure out some way to be able to compare these and have them
  // represent cardinal elements via string comparison
  START = new SkiplistNode(max_level, "", "");
  END = new SkiplistNode(max_level, "", "");

  // Connect the start and end nodes
  for (int i = 0; i < max_level; i++) {
    START->next[i] = END;
  }
}

std::optional<std::string> Skiplist::Search(std::string Key) {

  auto current = START;
  auto max_search_level = max_level - 1;
  std::cout << "Max search Level -> " << max_search_level << std::endl;

  for (int i = max_search_level; i >= 0; i--) {
    std::cout << "Searching in Level -> " << i << std::endl;
    while (current->next[i]->key < Key) {
      std::cout << "Testing current key -> " << current->next[i]->key
                << std::endl;
      current = current->next[i];
    }
  }
  current = current->next[1];
  if (current->key == Key) {
    return std::optional<std::string>{current->value};
  } else {
    return std::nullopt;
  }
}

// This is called insert but it has upsert semantics
std::pair<std::string, SkiplistError>
Skiplist::Insert(const std::string &key, const std::string &value) {

  // decide whether or not to skip searching
  auto skipSearch = START->next[0] == END;

  // Initialize the update vector
  auto update = std::vector<SkiplistNode *>(max_level);

  // See if the node already exists
  auto current = START;
  auto max_search_level = max_level - 1;
  std::cout << "Max search Level -> " << max_search_level << std::endl;

  for (int i = max_search_level; i >= 0; i--) {
    std::cout << "Searching in Level -> " << i << std::endl;
    while (current->next[i]->key < key) {
      std::cout << "Testing current key -> " << current->next[i]->key
                << std::endl;
      current = current->next[i];
    }
    update[i] = current;
  }
  current = current->next[1];
  if (current->key == key) {
    auto oldVal = current->value;
    current->value = value;
    return std::make_pair(oldVal, SkiplistError::NOERR);
  }

  std::cout << "Old node not present!" << std::endl;

  // The node doesn't exist;
  // Construct a new node
  int level = getRandomLevel();

  // WARN
  // Not doing this rn: need to update the max level of the list if this happens
  // I doubt it will but the paper says we need to do it so ¯\_(ツ)_/¯
  if (level > max_level) {
  }

  auto new_node = new SkiplistNode(level, key, value);
  for (int i = 0; i < level; i++) {
    new_node->next[i] = update[i]->next[i];
    update[i]->next[i] = new_node;
  }

  // Update all the pointers in the reachability chain to reach this node
  return std::make_pair(value, SkiplistError::NOERR);
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

int Skiplist::getRandomLevel() {
  int level = 1;
  while ((distribution(rng) < p) && (level < max_level)) {
    level += 1;
  }
  return level;
}
