#
#   Filename	Makefile
#   Date		2/26/2019
#   Author	Basil Elhindi
#   Email	bae170000@utdallas.edu
#   Course	CS 3377.502 Spring 2019
#   Version	1.0
#   Copyright 2019, All Rights Reserved
#
#   Description
#     Make file meant to compile C++ source code as well as clean up the directory and create a tarball.
#
#

hw3: hw3runner.o popen.o
	g++ hw3runner.o popen.o -o hw3

hw3runer.o: hw3runner.cpp hw3header.h
	g++ -Wall -c hw3runner.cpp

popen.o: hw3header.h popen.cpp
	g++ -Wall -c popen.cpp

clean:
	rm -f *~
	rm -f hw3runner.o
	rm -f popen.o
	rm -f hw3
