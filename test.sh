#!/bin/bash

# Exit on error
set -e  

# todo do this for all .c files in ./tests/

# Build specified test file with GCC args for testing and coverage
export GCC_ARGS="-lcunit -fprofile-arcs -ftest-coverage"
./build.sh $1

# Run valgrind to test for memory leaks 
# Run the tests reporting to an xml file
valgrind --leak-check=full --xml=yes --xml-file=build/test-list-valgrind-report.xml ./build/test_list.out build/test-list
# Prettify valgrind results
mkdir -p "build/valgrind-reports"
xsltproc valgrind-report.xsl build/test-list-valgrind-report.xml > build/valgrind-reports/test-list-valgrind-report.html
# Prettify the test results
mkdir -p "build/test-reports"
xsltproc cunit-report.xsl build/test-list-Results.xml > build/test-reports/test-list-report.html

# Generate coverage information
cd build
gcov *.gcno
cd ..

# Generate coverage report
lcov --capture --directory build --output-file build/coverage.info
# Prettify the coverage results
mkdir -p "build/coverage-report"
genhtml build/coverage.info --output-directory build/coverage-report
