/*
  Filename     popen.cpp
  Date         4/23/2019
  Author       Basil Elhindi
  Email        bae170000@utdallas.edu
  Course       CS 3377.502 Spring 2019
  Version      1.0
  Copyright 2019, All Rights Reserved

  Description
    C++ source file that uses popen to pipe the result of date.
*/

#define BUFFER_SIZE 1024

#include <stdio.h>
#include <stdlib.h>
#include "header.h"

string getLine()
{
  FILE *commandoutput;
  char tempbuffer[BUFFER_SIZE];
  char* line;
  string shellcmd = "date +.%Y.%m.%d-%I:%M:%S";
  commandoutput = popen(shellcmd.c_str(), "r");
  if(!commandoutput)
    return "error";
  string date = "";
  line = fgets(tempbuffer, BUFFER_SIZE, commandoutput);
  date = line;
  pclose(commandoutput);
  return date;
}
