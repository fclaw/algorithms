#!/bin/bash

# Usage:
# ./script.sh compile source.cpp
# ./script.sh run source.cpp ./testfile.txt [outfile.txt]

action=$1
source=$2
testfile=${3:-./algorithms/onlinejudge/test}
outfile=$4

if [ "$action" == "compile" ]; then
    g++ -std=c++20 -O2 -Wall "$source" -o exe
    if [ $? -eq 0 ]; then
        echo "Compilation successful."
    else
        echo "Compilation failed."
        exit 1
    fi

elif [ "$action" == "run" ]; then
    if [ ! -f exe ]; then
        echo "Executable not found. Compile first."
        exit 1
    fi
    if [ ! -f "$testfile" ]; then
        echo "Test file '$testfile' not found."
        exit 1
    fi

    if [ -n "$outfile" ]; then
        ./exe < "$testfile" > "$outfile"
        echo "Output written to $outfile"
    else
        ./exe < "$testfile"
    fi

else
    echo "Usage:"
    echo "  $0 compile <source.cpp>"
    echo "  $0 run <source.cpp> <testfile.txt> [output.txt]"
    exit 1
fi