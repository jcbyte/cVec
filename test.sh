#!/bin/bash

export GCC_ARGS="-lcunit -fprofile-arcs -ftest-coverage"
./build.sh $1

./build/test_list.out

xsltproc cunit-to-html.xsl build/test_results.xml-Results.xml > build/test_results-Results.html

cd build
gcov *.gcno
cd ..

lcov --capture --directory build --output-file build/coverage.info
genhtml build/coverage.info --output-directory build/coverage-report
