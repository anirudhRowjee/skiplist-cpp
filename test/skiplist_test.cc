#include "sl/skiplist.h"
#include <fmt/core.h>
#include <gtest/gtest.h>
#include <string>

TEST(SkiplistTest, test_init) {
  // Initialize a Skiplist
  const int max_level = 5;
  auto sl = Skiplist(max_level);
  for (int i = 0; i < max_level; i++) {
    ASSERT_EQ(sl.START->links[i], sl.END);
  }
}

TEST(SkiplistTest, test_insert) {

  auto linear_search = [](std::string key,
                          Skiplist sl) -> SkiplistError::ErrorVariant {
    auto curr_node = sl.START;
    while (curr_node != sl.END) {
      if (curr_node->key != key) {
        curr_node = curr_node->links[0];
      } else {
        return SkiplistError::ErrorVariant::NOERR;
      }
    }
    return SkiplistError::ErrorVariant::KEY_NOT_FOUND;
  };

  // Check the monotonicity of the keys
  auto monotonicity_check = [](Skiplist sl) -> SkiplistError {};

  const int max_level = 5;
  std::cout << fmt::format("initializing skiplist with level {}", max_level)
            << std::endl;
  auto sl = Skiplist(max_level);
  sl.DUMP();

  std::vector<std::tuple<std::string, std::string>> kvPairs = {
      {"hello", "world"},   {"something", "else"},
      {"enter", "sandman"}, {"the struts", "could have been me"},
      {"hello", "world2"},  {"END_KEY", "SYSTEM BROKEN!!!"}};

  for (auto [key, value] : kvPairs) {
    // Insert an element and search for it
    auto [retval, err] = sl.Insert(key, value);
    ASSERT_EQ(err.e, SkiplistError::NOERR);
    // Do a simple linear search
    ASSERT_EQ(linear_search(key, sl).e, SkiplistError::NOERR);
    // Ensure that monotonicity is maintained

    sl.DUMP();
  }
}

TEST(SkiplistTest, test_insert_and_search) {
  const int max_level = 5;
  std::cout << fmt::format("initializing skiplist with level {}", max_level)
            << std::endl;
  auto sl = Skiplist(max_level);
  sl.DUMP();

  // Load some data into the skiplist
  std::vector<std::tuple<std::string, std::string>> kvPairs = {
      {"hello", "world"},
      {"something", "else"},
      {"enter", "sandman"},
      {"martin garrix", "under pressure"},
      {"the smiths", "please please please let me get what I want"},
      {"the struts", "could have been me"},
      {"hello", "world2"}};
  for (auto [key, value] : kvPairs) {
    auto [retval, err] = sl.Insert(key, value);
    ASSERT_EQ(err.e, SkiplistError::NOERR);
  }

  sl.DUMP();

  // Search for elements in the skiplist
  std::vector<std::tuple<std::string, std::optional<std::string>>> testcases = {
      {"something", "else"},
      {"enter", "sandman"},
      {"the struts", "could have been me"},
      {"martin garrix", "under pressure"},
      {"this isn't there", std::nullopt},
      {"the smiths", "please please please let me get what I want"},
      {"hello", "world2"},
      {"nonexistent", std::nullopt}};
  for (auto [key, searchResult] : testcases) {
    ASSERT_EQ(sl.Search(key), searchResult);
  }
}

TEST(SkiplistTest, test_delete) {
  const int max_level = 5;
  std::cout << fmt::format("initializing skiplist with level {}", max_level)
            << std::endl;
  auto sl = Skiplist(max_level);

  // Load some data into the skiplist
  std::vector<std::tuple<std::string, std::string>> kvPairs = {
      {"hello", "world"},
      {"something", "else"},
      {"enter", "sandman"},
      {"martin garrix", "under pressure"},
      {"the smiths", "please please please let me get what I want"},
      {"the struts", "could have been me"},
      {"hello", "world2"}};
  for (auto [key, value] : kvPairs) {
    auto [retval, err] = sl.Insert(key, value);
    ASSERT_EQ(err.e, SkiplistError::NOERR);
  }
}
