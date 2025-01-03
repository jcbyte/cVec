#!/bin/bash

# Exit on error
set -e  

: ${WORKSPACE:=$PWD}
OUTPUT_DIR="${WORKSPACE}/build"

# Ensure output directory's exists
mkdir -p "$OUTPUT_DIR"
mkdir -p "$OUTPUT_DIR/test-reports"
mkdir -p "$OUTPUT_DIR/valgrind-reports"
mkdir -p "$OUTPUT_DIR/coverage-report"

# Run specific test if argument is passed
if [[ -n "$1" ]]; then
    files=("tests/$1.c")
else
    files=($(find tests/ -name "*.c"))
fi

# Specify GCC args for testing and coverage
export GCC_ARGS="-lcunit -fprofile-arcs -ftest-coverage"

# Build and run all tests
for file in "${files[@]}"; do
    test_name=$(basename $file .c)

    # Build specified test file
    ./build.sh $file
    compiled_test="$OUTPUT_DIR/${test_name}.out"

    # Run valgrind to test for memory leaks 
    # Run the tests reporting to an xml file
    valgrind_report="$OUTPUT_DIR/${test_name}-valgrind-report.xml"
    valgrind --leak-check=full --xml=yes --xml-file=$valgrind_report $compiled_test "$OUTPUT_DIR/$test_name"
    test_report="$OUTPUT_DIR/${test_name}-Results.xml"
    # Prettify the test results
    xsltproc cunit-report.xsl $test_report > "$OUTPUT_DIR/test-reports/$test_name-report.html"
    # Prettify valgrind results
    xsltproc valgrind-report.xsl $valgrind_report > "$OUTPUT_DIR/valgrind-reports/$test_name-valgrind-report.html"
done

# Generate coverage information
cd $OUTPUT_DIR
gcov *.gcno
cd ..

# Generate coverage report
lcov --capture --directory $OUTPUT_DIR --output-file $OUTPUT_DIR/coverage.info
# Prettify the coverage results
genhtml $OUTPUT_DIR/coverage.info --output-directory $OUTPUT_DIR/coverage-report
