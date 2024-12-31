#!/bin/bash

# Variables
GCC="/usr/bin/gcc"
OUTPUT_DIR="${PWD}/build"

# Ensure output directory exists
mkdir -p "$OUTPUT_DIR"

# Compile the file
OUTPUT_FILE="${OUTPUT_DIR}/$(basename "$1" .c).out"
$GCC -fdiagnostics-color=always -g "$1" "${PWD}/list/"*.c -o $OUTPUT_FILE -lcunit

# Display success and give path to built file
echo "Build successful! Output: ${OUTPUT_FILE}"
