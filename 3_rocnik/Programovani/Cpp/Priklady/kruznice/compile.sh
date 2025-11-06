#!/bin/bash
# Compilation script for kruznice project

echo "Compiling kruznice project..."
if g++ -o main main.cpp kruznice.cpp bod.cpp; then
    echo "✓ Compilation successful!"
    echo "Run with: ./main"
else
    echo "✗ Compilation failed!"
    exit 1
fi
