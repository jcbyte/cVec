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

# Compile all files
for file in "${files[@]}"; do
    lib_name=$(basename $file .c)

    # Compile object file
    gcc -c $file -o "${OUTPUT_DIR}/${lib_name}.o"
    if [ $? -ne 0 ]; then
        echo -e "\033[1;31mError compiling\033[0m \033[36m${file}\033[0m\n"
        exit 1
    fi
    # Create static library
    ar rcs "${OUTPUT_DIR}/lib${lib_name}.a" "${OUTPUT_DIR}/${lib_name}.o"
     if [ $? -ne 0 ]; then
        echo -e "\033[1;31mError creating static library for\033[0m \033[36m${file}\033[0m\n"
        exit 1
    fi
    rm ${OUTPUT_DIR}/${lib_name}.o

    # Create shared library
    gcc -shared -o "${OUTPUT_DIR}/lib${lib_name}.so" $file
    if [ $? -ne 0 ]; then
        echo -e "\033[1;31mError creating shared library for\033[0m \033[36m${file}\033[0m\n"
        exit 1
    fi
done

echo -e "\n\033[1;32mCompiling successful.\033[0m - \033[36m${OUTPUT_DIR}\033[0m\n"
