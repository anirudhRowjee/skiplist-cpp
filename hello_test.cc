#include "skiplist/skiplist.h"
#include <gtest/gtest.h>

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}

TEST(SkiplistTest, test_init) {

  // Initialize a Skiplist
  const int max_level = 5;
  auto sl = Skiplist(max_level);

  for (int i = 0; i < max_level; i++) {
    ASSERT_EQ(sl.START->next[i], sl.END);
  }
}
