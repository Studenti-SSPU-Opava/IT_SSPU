#!/bin/bash
# Compilation script for kruznice project

echo "Compiling kruznice project..."
g++ -o main main.cpp kruznice.cpp bod.cpp

if [ $? -eq 0 ]; then
    echo "✓ Compilation successful!"
    echo "Run with: ./main"
else
    echo "✗ Compilation failed!"
    exit 1
fi
