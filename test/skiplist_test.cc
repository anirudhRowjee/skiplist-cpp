#include "sl/skiplist.h"
#include <gtest/gtest.h>
#include <string>

TEST(SkiplistTest, test_init) {
  // Initialize a Skiplist
  const int max_level = 5;
  auto sl = Skiplist(max_level);
  for (int i = 0; i < max_level; i++) {
    ASSERT_EQ(sl.START->next[i], sl.END);
  }
}

TEST(SkiplistTest, test_insert) {
  // Initialize a Skiplist
  const int max_level = 5;
  auto sl = Skiplist(max_level);

  // Insert an element and search for it
  auto [value, err] = sl.Insert("hello", "world");
  std::cout << "Inserted" << std::endl;
  ASSERT_EQ(err.e, SkiplistError::NOERR);

  // sl.Delete("hello");
  // ASSERT_EQ(err.e, SkiplistError::ErrorVariant::BAD_ACCESS);
  // ASSERT_FALSE(err);
}
