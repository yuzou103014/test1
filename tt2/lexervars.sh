#!/bin/bash

# Ensure the bin directory exists
mkdir -p bin

# Compile the lexer
make

# Check if the lexer was compiled successfully
if [ ! -f bin/lexer ]; then
    echo "Error: Lexer compilation failed."
    exit 1
fi

# Run the lexer with input from stdin
bin/lexer