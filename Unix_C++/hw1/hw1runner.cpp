/*
  Filename hw1runner.cpp
  Date     1/31/2019
  Author   Basil Elhindi
  Email    bae170000@utdallas.edu
  Course   CS 3377.502 Spring 2019
  Version  1.0
  Copyright 2019, All Rights Reserved

  Description
    C++ source file with main method to run functions from anoter c++ source file.
*/

#include <iostream>
#include "hw1header.h"
using namespace std;

int main(int argc, char* argv[])
{
  //print arg count including the file name
  cout << argc << "\n" << endl;
  //print args in order including arg[0] which is the file name
  for(int i=0; i<argc; i++)
    cout << argv[i] << "\n";
  cout << "\n";
  printerr();
  return 0;
}
