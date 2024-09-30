# Skiplist
A simple skiplist implementation in C++. Currently, does not track the max key level for the skiplist.

## Building

Please ensure you have CMake installed. This project works on CMake 3.30 and with C++ 20.

```bash
mdkir build && cd build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..
cmake --build build
./build/skiplist_test
```
