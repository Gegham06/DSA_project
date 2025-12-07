#!/bin/bash

# Get project root (one directory up from the script location)
PROJECT_ROOT="$(cd "$(dirname "$0")/.." && pwd)"

echo "Running clang-format in project root: $PROJECT_ROOT"

# Find matching files (excluding hidden & build dirs)
files=$(find "$PROJECT_ROOT" \
  -type d \( -name ".*" -o -iname "build*" \) -prune -false -o \
  -type f \( -name "*.cpp" -o -name "*.hpp" -o -name "*.cc" -o -name "*.c" -o -name "*.h" \))

if [ -z "$files" ]; then
    echo "No source files found to format."
    exit 0
fi

# Run clang-format
echo "$files" | xargs clang-format -i

# Print unique directories that contained formatted files
echo
echo "Formatted files were found in these directories:"
echo "$files" | xargs -n1 dirname | sort -u

echo
echo "Formatting completed in project: $PROJECT_ROOT"
