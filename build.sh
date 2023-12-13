#!/bin/bash

mkdir -p bin/

ASSIGN="${1:-assignment-1a}"

cd ./bin

gcc -g ../src/"${ASSIGN}".c -o "${ASSIGN}" -lc -lpthread -lm -lrt

cd ..
