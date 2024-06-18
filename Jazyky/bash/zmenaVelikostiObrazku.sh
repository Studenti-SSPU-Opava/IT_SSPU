#!/bin/bash

# Check if 'convert' command is installed
if ! command -v convert &> /dev/null; then
    echo "The 'convert' command is not installed. Installing..."
    sudo apt-get install imagemagick
fi

# Get the input and output paths from command line arguments
input_path="$1"
output_path="$2"

# Resize the image(s)
convert "$input_path" -resize 800x600 "$output_path"