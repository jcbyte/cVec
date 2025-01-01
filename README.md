# cVec

This project provides a basic implementation of a singly linked list in C.

## Installation

_todo: Need to work out how to package_

## Usage

Example code given in [example.c](./example.c).

- Functions in the linked list can be found in [list.h](./list/list.h) and act similarly to to [std::vector](https://en.cppreference.com/w/cpp/container/vector#Member_functions).

## Testing

1. Install CUnit:
```bash
sudo apt-get install libcunit1-dev
```
   
2. Compile the test files (replacing `test_file.c` with the specified test file):
```bash
./build.sh tests/test_file.c
```
   
3. Run the tests:
```bash
./build/test_file.out
```

## Authors

- [@jcbyte](https://www.github.com/jcbyte)