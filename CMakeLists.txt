cmake_minimum_required(VERSION 3.14)
project(my_project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


enable_testing()

add_executable(
  hello_test
  hello_test.cc
)

add_executable(
  main
  main.cc
)

add_subdirectory(skiplist)

# why do we need this? idk
target_include_directories(main PUBLIC
  "${PROJECT_BINARY_DIR}"
  "${PROJECT_BINARY_DIR}/skiplist"
)

target_link_libraries(
  main
  PUBLIC skiplist
)

target_link_libraries(
  hello_test
  PUBLIC skiplist
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(hello_test)
