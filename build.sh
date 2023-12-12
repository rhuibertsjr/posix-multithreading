#!/bin/bash

mkdir -p bin/

cd ./bin

gcc -g -O0 ../src/main.c -o app

cd ..
