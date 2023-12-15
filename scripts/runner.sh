#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <script_name> <number_of_times>"
    exit 1
fi

program=$1
times=$2

echo "Running $program for $times times."

for ((i=1; i<=times; i++)); do
    "$program"
done