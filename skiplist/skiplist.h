#include <string>
#include <vector>

class SkiplistNode {
private:
  int current_level;
  std::string key;
  std::string value;
  std::vector<SkiplistNode *> next;
};

class Skiplist {

public:
  // constructor
  Skiplist(int max_level) { current_max_level = max_level; }

private:
  SkiplistNode *START;
  SkiplistNode *END;
  int max_level;
  int current_max_level;
};
