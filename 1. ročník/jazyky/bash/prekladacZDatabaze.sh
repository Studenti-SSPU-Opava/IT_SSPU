#!/bin/bash

#command translate
function translate() {
    alias trsl="translate"
    if [ $# -eq 0 ]; then 
    echo "No parameters provided.";
    else if [ $1 -eq 1 ]; then
        awk -f
    fi
}
