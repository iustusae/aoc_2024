#!/bin/bash

# Get the current day of December, removing leading zero
current_day=$(date +%-d)

# Validate the day is between 1 and 24
if [[ $current_day -lt 1 || $current_day -gt 24 ]]; then
    echo "Error: This script is only valid for days 1-24 in December."
    exit 1
fi

# Create directory for the current day
dir_name="day_$current_day"
mkdir -p "$dir_name/solutions"

curl https://adventofcode.com/2024/day/$(date +%-d) | pandoc -f html -t gfm+pipe_tables-raw_html > $dir_name/problem.md

echo "Created directory structure for Advent of Code Day $current_day"
echo "- Directory: $dir_name"
echo "- Subdirectory: $dir_name/solutions"
echo "- Problem description: $dir_name/problem.md"
