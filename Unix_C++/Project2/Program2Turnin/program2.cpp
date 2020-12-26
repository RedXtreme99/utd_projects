/*
  Filename   program2.cpp
  Date       2/7/2019
  Author     Basil Elhindi
  Email      bae170000
  Course     CS 3377.502 Spring 2019
  Version    1.0
  Copyright 2019, All Rights Reserved

  Description
    File containing main that calls the command line parser and reads the input file and writes it to an output file in the correct case.
*/

#include <iostream>
#include <fstream>
#include "header.h"
#include <cctype>
using namespace std;

//define map in just one place
map<int, string> myMap;

int main(int argc, char* argv[])
{
  //send the command line arguments to be parsed
  parseCommandLine(argc, argv);
  //take the input and output file from the map and open the streams to be read from and wrote to
  ifstream inputfile (myMap[INFILENAME]);
  ofstream outputfile (myMap[OUTFILENAME]);
  //check for u or l flag and capitalize appropriately. traverse the entire input file and print the output to the output file
  char c;
  if(inputfile.is_open())
  {
    if(myMap[UFLAG] == "true")
    {
      while(inputfile.get(c))
       {
	 if(c == '\n')
	   outputfile << endl;
         else outputfile << static_cast<char>(toupper(c));
       }
    }
    else if(myMap[LFLAG] == "true")
    {
      while(inputfile.get(c))
      {
	if(c == '\n')
	  outputfile << endl;
        else outputfile << static_cast<char>(tolower(c));
      }
    }
    else
    {
      while(inputfile.get(c))
	{
	  if(c == '\n')
	    outputfile << endl;
	  else outputfile << c;
	}
    }
  }
  else {cerr << "error"; return 1;}
  //close the input and output streams and exit the code
  outputfile.close();
  inputfile.close();
  return 0;
}
