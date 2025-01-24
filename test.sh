#!/bin/bash

: ${WORKSPACE:=$PWD}
OUTPUT_DIR="${WORKSPACE}/build"

# List of errors occurred during testing
test_errors=()

# Ensure output directory's exists
mkdir -p "$OUTPUT_DIR"
mkdir -p "$OUTPUT_DIR/test-reports"
mkdir -p "$OUTPUT_DIR/valgrind-reports"
mkdir -p "$OUTPUT_DIR/coverage-report"

# Run specific test if argument is passed
if [[ -n "$1" ]]; then
    files=($1)
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
    # If build fails, log and skip to next test
    if [ $? -ne 0 ]; then
        test_errors+=("\033[1;37m$test_name\033[0m failed building.")
        continue
    fi
    compiled_test="$OUTPUT_DIR/${test_name}.out"

    # Run valgrind to test for memory leaks 
    # Run the tests reporting to an xml file
    valgrind_report="$OUTPUT_DIR/${test_name}-valgrind-report.xml"
    valgrind --error-exitcode=2 --leak-check=full --xml=yes --xml-file=$valgrind_report $compiled_test "$OUTPUT_DIR/$test_name"
    # If either the tests or valgrind fail, log
    valgrind_exit_code=$?
    if [ $valgrind_exit_code -eq 1 ]; then
        test_errors+=("\033[1;37m$test_name\033[0m failed tests.")
    fi
    if [ $valgrind_exit_code -eq 2 ]; then
        test_errors+=("\033[1;37m$test_name\033[0m failed valgrind test.")
    fi
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

# Display success or display errors
if [ ${#test_errors[@]} -eq 0 ]; then
  echo -e "\n\033[1;32mTest(s) successful.\033[0m\n"
else
  echo -e "\n\033[1;31mTest(s) unsuccessful:\033[0m"
  # Display errors
  for test_error in "${test_errors[@]}"; do
    echo -e "  - $test_error"
  done
  echo
  exit 1
fi
