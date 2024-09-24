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

  // Search for an element that doesn't exist
  ASSERT_EQ(sl.Search("key1"), std::nullopt);

  // Insert an element and search for it
  auto key = std::string("hello");
  auto value = std::string("world");

  sl.Insert(key, value);
  sl.Delete("test");
  // ASSERT_EQ(err.e, SkiplistError::ErrorVariant::BAD_ACCESS);
  // ASSERT_FALSE(err);
}
