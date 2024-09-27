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
FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  GIT_TAG        e69e5f977d458f2650bb346dadf2ad30c5320281) # 10.2.1
FetchContent_MakeAvailable(fmt)
enable_testing()

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

target_link_libraries(skiplist_test
PRIVATE
  GTest::gtest_main
  fmt::fmt
)

include(GoogleTest)
gtest_discover_tests(skiplist_test)
