#!/bin/bash

export GCC_ARGS="-lcunit -fprofile-arcs -ftest-coverage"
./build.sh $1

./build/test_list.out build/test_list

mkdir -p "build/test-reports"
xsltproc cunit-to-html.xsl build/test_list-Results.xml > build/test-reports/test_list-Results.html

cd build
gcov *.gcno
cd ..

lcov --capture --directory build --output-file build/coverage.info
mkdir -p "build/coverage-report"
genhtml build/coverage.info --output-directory build/coverage-report
