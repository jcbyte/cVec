#!/bin/bash

: ${WORKSPACE:=$PWD}
OUTPUT_DIR="${WORKSPACE}/lib"

# Ensure output directory's exists
mkdir -p "$OUTPUT_DIR"

# todo - build all libraries
# gcc -c src/list.c -o "${OUTPUT_DIR}/list.o"
# ar rcs "${OUTPUT_DIR}/liblist.a" "${OUTPUT_DIR}/list.o"

# gcc -shared -o "${OUTPUT_DIR}/liblist.so" src/list.c