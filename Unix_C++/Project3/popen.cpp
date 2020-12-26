/*
  Filename     popen.cpp
  Date         2/26/2019
  Author       Basil Elhindi
  Email        bae170000@utdallas.edu
  Course       CS 3377.502 Spring 2019
  Version      1.0
  Copyright 2019, All Rights Reserved

  Description
    C++ source file that uses popen to capture the output of a gawk file and return the string of characters.
*/

#define BUFFER_SIZE 1024

#include <stdio.h>
#include <stdlib.h>
#include "hw3header.h"

string getLine()
{
  FILE *commandoutput;
  char tempbuffer[BUFFER_SIZE];
  char* line;
  string shellcmd = "/home/011/b/ba/bae170000/Program3/bin/gawk -f gawk.code numbers.txt";
  commandoutput = popen(shellcmd.c_str(), "r");
  if(!commandoutput)
    return "error";
  string gawkline = "";
  line = fgets(tempbuffer, BUFFER_SIZE, commandoutput);
  gawkline = line;
  pclose(commandoutput);
  return gawkline;
}
