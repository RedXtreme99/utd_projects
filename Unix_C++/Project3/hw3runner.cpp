/*
  Filename     hw3runner.cpp
  Date         2/26/2019
  Author       Basil Elhindi
  Email        bae170000@utdallas.edu
  Course       CS 3377.502 Spring 2019
  Version      1.0
  Copyright 2019, All Rights Reserved

  Description
    C++ source file containing main routine for homework 3 for getting number output from a gawk file and adding them.

*/
#include <stdlib.h>
#include <sstream>
#include "hw3header.h"

int main(int argc, char * argv[])
{
  cout << "gawk at: /home/011/b/ba/bae170000/Program3/bin/gawk" << endl;
  cout << "Shellcmd1: /home/011/b/ba/bae170000/Program3/bin/gawk --version" << endl;
  cout << "Shellcmd2: /home/011/b/ba/bae170000/Program3/bin/gawk -f gawk.code numbers.txt\n" << endl;
  //print version of gawk
  cout << "The first call to gawk returned:\n\n"; 
  system("./bin/gawk --version");
  //capture gawk output as a string and split it into two integers and add them
  string gawkout = getLine();
  cout << "\n\nThe second call to gawk returned: " <<  gawkout << endl << endl;
  int n1, n2;
  stringstream ss(gawkout);
  ss >> n1 >> n2; 
  cout << "The sum of column one is: " << n1 << endl;
  cout << "The sum of column four is: " << n2 << endl;
  cout << "The sum of the two numbers is: " << n1+n2 << endl;
  return 0;
}
