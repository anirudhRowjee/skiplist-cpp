cmake_minimum_required(VERSION 3.30)
project(skiplist-cpp VERSION 0.1
  DESCRIPTION "A Skiplist implemented in C++"
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(main
  main.cc
  skiplist/skiplist.cc
)
target_include_directories(main 
PUBLIC 
include 
"${PROJECT_BINARY_DIR}"
"${PROJECT_SOURCE_DIR}/include"
)


add_executable(skiplist_test
  test/skiplist_test.cc
  skiplist/skiplist.cc
)
target_include_directories(skiplist_test 
PUBLIC 
include 
"${PROJECT_BINARY_DIR}"
"${PROJECT_SOURCE_DIR}/include"
)

target_link_libraries(
  skiplist_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(skiplist_test)
