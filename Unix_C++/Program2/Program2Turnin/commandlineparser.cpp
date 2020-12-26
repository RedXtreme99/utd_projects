/*
  Filename   commandlineparser.cpp
  Date       2/7/2019
  Author     Basil Elhindi
  Email      bae170000@utdallas.edu
  Course     CS 3377.502 Spring 2019
  Version    1.0
  Copyright 2019, All Rights Reserved

  Description
    Function to process the command line arguments and query the parsing results into the map. TCLAP also looks for any mistakes in the command line arguments
    and throws an exception and prints the usage.
*/

#include <string>
#include <iostream>
#include <algorithm>
#include <tclap/CmdLine.h>
#include "header.h"
using namespace std;

void parseCommandLine(int argc, char* argv[])
{
  TCLAP::CmdLine cmd("CS 3377 Program2", ' ', "1.0");
  //everything wrapped in a try-catch block so TCLAP handles all errors on the command line
  try{
    //makes the -l and -u flags as switch args that are optional
    TCLAP::SwitchArg lowerArg("l", "lower", "Convert all text to lowercase", cmd,  false);
    TCLAP::SwitchArg upperArg("u", "upper", "Convert all text to uppercase", cmd, false);
    //create and add -o flag that can take an output filename, optional
    TCLAP::ValueArg<string> outfileArg("o", "outfile","The name of the output file", false, "output.txt", "output filename");
    cmd.add(outfileArg);
    //create a no flag argument that is a required input filename
    TCLAP::UnlabeledValueArg<string> infileArg("infile", "Input file",  true, "infile.txt", "input filename", false);
    cmd.add(infileArg);
    //parses command line given the arguments from the command line called from program2.cpp
    cmd.parse(argc, argv);
    //assigns the values of the flags to the enumerated type keys
    myMap[INFILENAME] = infileArg.getValue();
    myMap[OUTFILENAME] = outfileArg.getValue();
    //converts boolean from switch args to string version of true or false to be placed in the map
    if(lowerArg.getValue())
      myMap[LFLAG] = "true";
    else myMap[LFLAG] = "false";
    if(upperArg.getValue())
      myMap[UFLAG] = "true";
    else myMap[UFLAG] =  "false";
    //if both u and l flag are present, throw an exception and print the usage
    if(upperArg.getValue() && lowerArg.getValue())
    {
      throw TCLAP::ArgException("error: -l and -u cannot both be present.");
      cmd.getOutput()->usage(cmd);
    }
  }
  //for any other error picked up by TCLAP, print the error and print usage
  catch (TCLAP::ArgException &e)
  {
    cerr << "error: " << e.error() << " for arg " << e.argId() << endl;
    cmd.getOutput()->usage(cmd);
  }
}
