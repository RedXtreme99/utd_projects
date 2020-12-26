/*
  Filename hw1printfuncs.cpp
  Date     1/31/2019
  Author   Basil Elhindi
  Email    bae170000@utdallas.edu
  Course CS 3377.502 Spring 2019
  Version 1.0
  Copyright 2019, All Rights Reserved

  Description
    C++ source file with functions to print values to standard output and error.
*/

#include <iostream>
#include "hw1header.h"
using namespace std;

void printerr()
{
  //print to standard error
  cerr << "Log message: in standard error" << endl;
}
