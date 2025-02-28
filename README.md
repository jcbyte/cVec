# cVec

C library implementing a dynamic array (vector) and a singly linked list, complete with unit testing and CI/CD.

## Installation

Precompiled binaries are available in [Releases](https://github.com/jcbyte/cVec/releases), these contain both static and shared libraries for Linux.

## Usage

Example usage can be seen in the [examples](./examples) directory.

Function definitions are available there respective `.h` files and the API acts similarly to [std::vector](https://en.cppreference.com/w/cpp/container/vector#Member_functions)'s.

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

## Licence

[Apache License 2.0](LICENSE)
