# cVec

This project provides a basic implementation of a singly linked list in C.

Soon to include a Vector!

Fully implemented testing and CI using GitHub actions.

## Installation

_todo: Need to work out how to package._

## Usage

Example code given shown in [examples](./examples).

Function definitions can be found in there respective `.h` files and act similarly to to [std::vector](https://en.cppreference.com/w/cpp/container/vector#Member_functions).

## Testing

Unit tests are written using CUnit.

### 1. Install Dependencies:
```bash
sudo apt install gcc libcunit1-dev valgrind xsltproc lcov
```
   
### 2. Run Tests

- Run all tests
```bash
./test.sh
```

- Run a specific test:
```bash
./test.sh tests/test_list.c
```
   
### 3. Check Reports (if required) at
- Test reports:  
  `./build/test-reports/`
  
- Valgrind memory check reports:  
  `./build/valgrind-reports/`
  
- Code coverage report:  
  `./build/coverage-report/`

## Authors

- [@jcbyte](https://www.github.com/jcbyte)