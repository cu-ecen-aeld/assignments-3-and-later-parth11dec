#!/bin/sh

# Check for required arguments
if [ $# -ne 2 ]; then
  echo "Error: Two arguments required: filesdir and searchstr"
  exit 1
fi

filesdir="$1"
searchstr="$2"

# Check if filesdir is a directory
if [ ! -d "$filesdir" ]; then
  echo "Error: '$filesdir' is not a directory"
  exit 1
fi

# Count files and matching lines
num_files=$(find "$filesdir" -type f | wc -l)
num_matches=$(grep -r "$searchstr" $filesdir | wc -l)

echo "The number of files are $num_files and the number of matching lines are $num_matches"
