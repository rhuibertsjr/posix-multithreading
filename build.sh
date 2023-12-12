#!/bin/bash

mkdir -p bin/

ASSIGN="${1:-assignment-1a}"

cd ./bin

gcc -g -O0 -lpthread -lc ../src/"${ASSIGN}".c -o "${ASSIGN}"

cd ..
