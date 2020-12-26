/*
  Filename  header.h
  Date      4/18/2019
  Author    Basil Elhindi
  Email     bae170000@utdallas.edu
  Course    CS 3377.502 Spring 2019
  Version   1.0
  Copyright 2019, All Rights Reserved
  
  Description
    Header file containing function prototypes and map definition.
*/

#ifndef _HEADER_H_
#define _HEADER_H_

#include <string>
#include <map>
using namespace std;

enum mapkeys {DAEMONARG=0, CONFIGFILENAME, VERBOSE, LOGFILE, PASSWORD, NUMVERSIONS, WATCHDIR};
extern map<int, string> myMap;
int configure();
void signalHandle(int sig);
void parseCmdLine(int count, char* vals[]);
int folderWatch();
string getLine();

#endif
