#include "skiplist/skiplist.h"
#include <iostream>

int main() {
  Skiplist l;
  l.set_a(100);
  std::cout << "New value of a -> " << l.get_a() << std::endl;
  std::cout << "Hello, world!" << std::endl;
  std::cout << "This is a new library" << std::endl;
}
