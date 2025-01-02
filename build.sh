#!/bin/bash

: ${WORKSPACE:=$PWD}

# Variables
GCC="/usr/bin/gcc"
OUTPUT_DIR="${WORKSPACE}/build"
LIB=("${WORKSPACE}/list/"*.c "${WORKSPACE}/vector/"*.c)

# Ensure output directory exists
mkdir -p "$OUTPUT_DIR"

# Compile the file
OUTPUT_FILE="${OUTPUT_DIR}/$(basename "$1" .c).out"
$GCC -fdiagnostics-color=always -g "$1" "${LIB[@]}" -o $OUTPUT_FILE $GCC_ARGS

# Display success and give path to built file
if [ $? -eq 0 ]; then
  echo -e "\n\033[1;32mBuild successful.\033[0m - \033[36m${OUTPUT_FILE}\033[0m\n"
else
  echo -e "\n\033[1;31mBuild unsuccessful.\033[0m\n"
  exit 1
fi

