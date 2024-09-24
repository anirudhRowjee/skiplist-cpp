#include "sl/skiplist.h"
#include <iostream>

int main() {
  auto k = Skiplist(10);
  k.Search("lol");
  k.Insert("a", "b");
  std::cout << "Hello, world!" << std::endl;
  std::cout << "This is a new library" << std::endl;
}
