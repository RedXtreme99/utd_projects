#!/bin/bash

#Filename  shellscript1.sh
#Date      1/31/2019
#Author    Basil Elhindi
#Email     bae170000@utdallas.edu
#Course    CS 3377.502 Spring 2019
#Version 1.0
#Copyright 2019, All Rights Reserved
#
#Description
#  Shell script to compile the two C++ source files and link the intermediate object files to get an executable. The shell script echoes what it is
#  doing at each step.

echo "Setting TEMPDIR environment variable to /scratch"
TMPDIR=/scratch; export TMPDIR
echo "Compiling source file with main"
g++ -c hw1runner.cpp
echo "Compiling source file with printerr function"
g++ -c hw1printfuncs.cpp
echo "Linking two object files"
g++ hw1runner.o hw1printfuncs.cpp -o output.out
echo "Done"
