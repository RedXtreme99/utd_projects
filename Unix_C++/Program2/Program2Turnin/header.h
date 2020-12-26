/*
  Filename   header.h
  Date       2/7/2019
  Author     Basil Elhindi
  Email      bae170000@utdallas.edu
  Course     CS 3377.502 Spring 2019
  Version    1.0
  Copyright 2019, All Rights Reserved

  Description
    Header file containing enumerated data type, global map declaration, and function in commandlineparser.cpp
*/

#ifndef HEADER_H
#define HEADER_H

#include <map>
#include <string>
using namespace std;

//enum definition for map keys
enum hashkeys {INFILENAME, OUTFILENAME, UFLAG, LFLAG};
//global variable declaration of map
extern map<int, string> myMap;
void parseCommandLine(int argc, char* argv[]);

#endif
