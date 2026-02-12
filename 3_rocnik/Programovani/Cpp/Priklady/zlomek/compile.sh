#!/bin/bash
# Compilation script for zlomek project (no code yet)

echo "Compiling zlomek project..."
# Collect all C++ sources in this directory (none expected initially)
sources=( *.cpp )
if [ -e "${sources[0]}" ]; then
    echo "Found sources: ${sources[*]}"
    if g++ -o main "${sources[@]}"; then
        echo "✓ Compilation successful!"
        echo "Running ./main now (you can also run it manually with ./main)"
        exec ./main
    else
        echo "✗ Compilation failed!"
        exit 1
    fi
else
    echo "No source files (*.cpp) found. Nothing to compile."
    echo "Add your C++ sources (e.g., main.cpp) and rerun."
    exit 0
fi
