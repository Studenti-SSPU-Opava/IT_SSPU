#!/bin/bash
# Compilation script for prevodySoustav project

echo "Compiling prevodySoustav project..."
if g++ -o main main.cpp ps.cpp; then
    echo "✓ Compilation successful!"
    echo "Running ./main now (you can also run it manually with ./main)"
    # Run the program. Use exec so the script exits with the same status as the program.
    exec ./main
else
    echo "✗ Compilation failed!"
    exit 1
fi
