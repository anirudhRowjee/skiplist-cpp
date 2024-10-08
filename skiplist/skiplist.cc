#include "sl/skiplist.h"
#include <fmt/core.h>

#include <cstdlib>
#include <iostream>
#include <optional>
#include <random>
#include <utility>

Skiplist::Skiplist(int max_level) : max_level(max_level) {

  // TODO need to see if this suffices
  p = 0.5;
  rng = std::mt19937(std::time(nullptr)); // fixed seed as of now
  distribution = std::uniform_real_distribution<double>(0.0, 1.0);

  // Initialize the sentinel nodes
  // Need to figure out some way to be able to compare these and have them
  // represent cardinal elements via string comparison
  START = new SkiplistNode(max_level, "START_KEY", "START_VALUE");
  END = new SkiplistNode(max_level, "END_KEY", "END_VALUE");

  // Connect the start and end nodes
  for (int i = 0; i < max_level; i++) {
    START->links[i] = END;
  }
}

std::optional<std::string> Skiplist::Search(std::string Key) {

  std::cout << "Searching for -> " << Key << std::endl;
  auto current = START;
  auto max_search_level = max_level - 1;

  for (int i = max_search_level; i >= 0; i--) {
    while (current->links[i]->key < Key && current->links[i] != END) {
      std::cout << fmt::format("Exploring key -> {}", current->links[i]->key)
                << std::endl;
      current = current->links[i];
    }
  }
  current = current->links[0];
  if (current->key == Key) {
    return std::optional<std::string>{current->value};
  } else {
    return std::nullopt;
  }
}

std::pair<std::pair<SkiplistNode *, std::vector<SkiplistNode *>>, SkiplistError>
Skiplist::identifyPredecessorNode(std::string key) {

  // Initialize the update vector
  auto update = std::vector<SkiplistNode *>(max_level, nullptr);

  // See if the node already exists
  auto current_node = START;
  auto next_node = START;

  auto max_search_level = max_level - 1;
  for (int i = max_search_level; i >= 0; i--) {
    // Check if the next node in the level has a key that comes before our
    // search key

    // See if the next node is a sentinel element
    next_node = current_node->links[i];
    while (next_node->key < key && next_node != END) {
      current_node = next_node;
      next_node = current_node->links[i];
    }
    update[i] = current_node;
  }
  current_node = current_node->links[0];
  return std::make_pair(std::make_pair(current_node, update),
                        SkiplistError(SkiplistError::ErrorVariant::NOERR));
}

// This is called insert but it has upsert semantics
std::pair<std::string, SkiplistError>
Skiplist::Insert(const std::string &key, const std::string &value) {

  // Figure out where to insert the node: this is either the node with the same
  // key, so we can update the value, or we found the node right before the
  // insertion point so that we can insert after it
  auto [meta, error] = identifyPredecessorNode(key);
  if (error.e != SkiplistError::NOERR) {
    return std::make_pair("", error);
  }
  std::cout << "Predecessor Found!" << std::endl;

  auto [current_node, update] = meta;
  if (current_node->key == key) {

    // If the key exists at the current node, update its value
    std::cout << fmt::format("BAZINGA! Key {} found with value {}",
                             current_node->key, current_node->value)
              << std::endl;
    auto oldVal = current_node->value;
    current_node->value = value;
    return std::make_pair(value, SkiplistError::NOERR);

  } else {

    // If they key doesn't exist at the current node, insert it
    std::cout << "Node not found" << std::endl;
    // The node doesn't exist;
    // Construct a new node
    int level = getRandomLevel();

    // WARN
    // Not doing this rn: need to update the max level of the list if this
    // happens I doubt it will but the paper says we need to do it so ¯\_(ツ)_/¯
    if (level > max_level) {
    }

    auto new_node = new SkiplistNode(level, key, value);
    for (int i = 0; i < level; i++) {
      new_node->links[i] = update[i]->links[i];
      update[i]->links[i] = new_node;
    }

    // Update all the pointers in the reachability chain to reach this node
    return std::make_pair(value, SkiplistError::NOERR);
  }
}

std::pair<std::string, SkiplistError> Skiplist::Delete(std::string Key) {

  std::string oldVal;
  // Figure out where to delete the node: this is either the node with the same
  // key, so we can update the value, or we found the node right before the
  // insertion point so that we can insert after it
  auto [meta, error] = identifyPredecessorNode(Key);
  if (error.e != SkiplistError::NOERR) {
    return std::make_pair("", error);
  }
  auto [nodePtr, update] = meta;
  if (nodePtr->key == Key) {
    // We have found the right node to delete
    // update all the necessary pointers
    for (int i = 0; i < max_level; i++) {
      if (update[i]->links[i] != nodePtr) {
        break;
      }
      update[i]->links[i] = nodePtr->links[i];
    }
    oldVal = nodePtr->value;
    delete nodePtr;
    // TODO update overall list level
    return std::make_pair(oldVal,
                          SkiplistError(SkiplistError::ErrorVariant::NOERR));
  } else {
    return std::make_pair(
        "", SkiplistError(SkiplistError::ErrorVariant::KEY_NOT_FOUND));
  }

  return std::make_pair("",
                        SkiplistError(SkiplistError::ErrorVariant::BAD_ACCESS));
}

std::pair<std::vector<std::pair<std::string, std::string>>, SkiplistError>
Skiplist::Scan() {
  std::vector<std::pair<std::string, std::string>> answer = {};
  auto current_node = START->links[0];
  while (current_node != END) {
    answer.push_back(std::make_pair(current_node->key, current_node->value));
    current_node = current_node->links[0];
  }
  return std::make_pair(answer, SkiplistError(SkiplistError::NOERR));
}

Skiplist::~Skiplist() {
  std::cout << "Destructing Skiplist" << std::endl;
  auto [res, err] = Scan();
  if (err.e != SkiplistError::NOERR) {
  } else {
    for (auto [k, _] : res) {
      auto [res1, err1] = Delete(k);
      if (err1.e != SkiplistError::NOERR) {
        std::cout << fmt::format("Failed to delete key {}", res1) << std::endl;
      }
    }
  }
}

void Skiplist::DUMP() {
  std::cout << fmt::format("=== Printing Skiplist") << std::endl;
  auto itr_pointer = START;
  while (itr_pointer != nullptr) {
    itr_pointer->DUMP();
    itr_pointer = itr_pointer->links[0];
  }
  std::cout << fmt::format("=== END Printing Skiplist") << std::endl;
}

int Skiplist::getRandomLevel() {
  int level = 1;
  while ((distribution(rng) < p) && (level < max_level)) {
    level += 1;
  }
  return level;
}
