#include <optional>
#include <string>
#include <vector>

class SkiplistNode {
private:
  int current_level;
  std::string key;
  std::string value;

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

    // TODO
    // - Decide the level of this node with a randomized coin toss series
    // - make all the pointers in the next array null
  }

  // Function to remove all references in the `next` array.
  void EmptyNext();
};

class Skiplist {

public:
  // constructor
  Skiplist(int max_level);

  // Get the value associated with a particular key
  [[nodiscard]] std::optional<std::string> Search(std::string Key);

  // Insert a key-value pair
  std::optional<std::string> Insert(std::string key, std::string value);

  // Delete a key and get the value associated with it on successful delete
  std::optional<std::string> Delete(std::string key);

  // Do a full scan of the skiplist
  // TODO see if we can replace this with an iterator
  std::optional<std::vector<std::pair<std::string, std::string>>> Scan();

  SkiplistNode *START;
  SkiplistNode *END;
  int max_level;
  int current_max_level;
};
