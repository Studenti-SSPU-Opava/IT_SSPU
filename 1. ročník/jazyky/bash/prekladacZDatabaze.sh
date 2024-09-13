#!/bin/bash

#command translate
function translate() {
    alias trsl="translate"
    if [ $# -eq 0 ]; then 
    echo "No parameters provided.";
    fi
    elif [ $1 -eq 1 ]; then
        awk -f
    fi
}
