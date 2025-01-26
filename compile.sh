#!/bin/bash

: ${WORKSPACE:=$PWD}
OUTPUT_DIR="${WORKSPACE}/lib"

# Ensure output directory's exists
mkdir -p "$OUTPUT_DIR"

if [[ -n "$1" ]]; then
    files=($1)
else
    files=($(find src/ -name "*.c"))
fi

for file in "${files[@]}"; do
    lib_name=$(basename $file .c)
    gcc -c $file -o "${OUTPUT_DIR}/${lib_name}.o"
    ar rcs "${OUTPUT_DIR}/lib${lib_name}.a" "${OUTPUT_DIR}/${lib_name}.o"
    rm ${OUTPUT_DIR}/${lib_name}.o

    gcc -shared -o "${OUTPUT_DIR}/lib${lib_name}.so" $file
done

if [ $? -eq 0 ]; then
  echo -e "\n\033[1;Compiling successful.\033[0m - \033[36m${OUTPUT_DIR}\033[0m\n"
else
  echo -e "\n\033[1;31mCompiling unsuccessful.\033[0m\n"
  exit 1
fi
