#!/bin/bash

echo Compiling...
./Cpp/Master/comp.sh ./Cpp/Master/main.c test
echo Finished compiling. Starting emulation...

python3 Emulator.py &
./test

