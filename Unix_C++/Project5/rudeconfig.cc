/*
  Filename  rudeconfig.cc
  Date      4/23/19
  Author    Basil Elhindi
  Email     bae170000@utdallas.edu
  Course    CS 3377.502 Spring 2019
  Version   1.0
  Copyright 2019, All Rights Reserved

  Description
    File containing function to implement rude config.
*/

#include <rude/config.h>
#include <iostream>
#include "header.h"

int configure()
{
  rude::Config config;
  if(!config.load(myMap[CONFIGFILENAME].c_str()))
  {
    cerr << "Error: file does not exist" << endl;
    return 1;
  }
  if(!config.setSection("Parameters", false))
  {
    cerr << "Error: section Parameters does not exist" << endl;
    return 1;
  } 
  string verbose = "VERBOSE";
  string logfile = "LOGFILE";
  string password = "PASSWORD";
  string numVersions = "NUMVERSIONS";
  string watchDir = "WATCHDIR";
  if(!(config.exists(verbose.c_str()) && config.exists(logfile.c_str()) && config.exists(password.c_str()) && config.exists(numVersions.c_str()) && config.exists(watchDir.c_str())))
  {
    cerr << "Error: missing definitions in section Parameters" << endl;
    return 1;
  }
  myMap[VERBOSE] = config.getStringValue(verbose.c_str());
  myMap[LOGFILE] = config.getStringValue(logfile.c_str());
  myMap[PASSWORD] = config.getStringValue(password.c_str());
  myMap[NUMVERSIONS] = config.getStringValue(numVersions.c_str());
  myMap[WATCHDIR] = config.getStringValue(watchDir.c_str());
  return 0;
}

