# File Statistics Tool

A C++ command-line utility for analyzing text files and displaying various statistics, similar to the Unix `wc` command.

## Features

- **Line count** (`-l`): Count the number of lines
- **Word count** (`-w`): Count the number of words  
- **Byte count** (`-c`): Display file size in bytes
- **Character count** (`-m`): Count all characters
- **Longest line** (`-L`): Find the length of the longest line
- **Default output**: When no options are specified, shows lines, words, and bytes

## Compilation

```bash
g++ -std=c++11 -o file_stats main.cpp
