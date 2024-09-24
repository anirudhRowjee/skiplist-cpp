#include "sl/common.h"

#include <optional>
#include <random>
#include <string>
#include <vector>

class SkiplistNode {

public:
  // TODO see if we can mutate this without making it public
  // Maybe operator overload??
  std::vector<SkiplistNode *> next;

  // Constructor
  SkiplistNode(int current_level, std::string key, std::string value)
      : current_level(current_level), key(std::move(key)),
        value(std::move(value)) {

    next = std::vector<SkiplistNode *>(current_level);
    for (int i = current_level - 1; i >= 0; i--) {
      next[i] = nullptr;
    }
  }

  // Function to remove all references in the `next` array.
  void EmptyNext();

  int current_level;
  std::string key;
  std::string value;
};

class Skiplist {

public:
  // constructor
  Skiplist(int max_level);

  // Get the value associated with a particular key
  std::optional<std::string> Search(std::string Key);

  // Insert a key-value pair
  std::pair<std::string, SkiplistError> Insert(const std::string &Key,
                                               const std::string &Value);

  // Delete a key and get the value associated with it on successful delete
  std::pair<std::string, SkiplistError> Delete(std::string Key);

  // Do a full scan of the skiplist
  // TODO see if we can replace this with an iterator
  std::pair<std::vector<std::pair<std::string, std::string>>, SkiplistError>
  Scan();

  ~Skiplist();

  SkiplistNode *START;
  SkiplistNode *END;
  int max_level;
  int current_max_level;
  // p: a tunable factor for the number of elements you want in the skiplist
  float p;
  std::mt19937 rng;
  std::uniform_real_distribution<double> distribution;

  int getRandomLevel();
};
