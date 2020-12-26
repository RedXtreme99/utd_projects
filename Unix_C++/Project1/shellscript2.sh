#!/bin/bash

#Filename  shellscript2.sh
#Date      1/31/2019
#Author    Basil Elhindi
#Email     bae170000@utdallas.edu
#Course    CS 3377.502 Spring 2019
#Version   1.0
#Copyright 2019, All Rights Reserved
#
#Description
#  Shell script to run executable code with multiple arguments

echo "Running program with 0 arguments"
./output.out > stdout.log 2> stderr.log
echo "standard output appended to stdout.log"
echo "standard error appended to stderr.log"
echo "Running program with 1 argument"
./output.out abc >> stdout.log 2>> stderr.log
echo "standard output appended to stdout.log"
echo "standard error appended to stderr.log"
echo "Running program with 5 arguments"
./output.out a b c d e >> stdout.log 2>> stderr.log
echo "Done!"
echo "opening stdout.log"
cat stdout.log
echo "opening stderr.log"
cat stderr.log
