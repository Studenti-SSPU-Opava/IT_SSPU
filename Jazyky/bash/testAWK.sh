#!/bin/bash

# Check if the correct number of arguments are provided
if [ "$#" -ne 3 ]; then
  echo "Usage: $0 filename word column_number"
  exit 1
fi

# Assign the parameters to variables
filename=$1
word=$2
column=$3

# Check if the column number is a positive integer
if ! [[ "$column" =~ ^[1-9][0-9]*$ ]]; then
  echo "Error: column_number must be a positive integer."
  exit 1
fi

# Use awk to search for the word in the file and print the word from the specified column
awk -v searchWord="$word" -v col="$column" '
  {
    for (i = 1; i <= NF; i++) {
      if ($i == searchWord) {
        if (col <= NF) {
          print $col
        } else {
          print "Error: Specified column number exceeds the number of columns in the line."
        }
        exit
      }
    }
  }
' "$filename"
