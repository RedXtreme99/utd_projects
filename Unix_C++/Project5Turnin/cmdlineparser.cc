/*
  Filename  cmdlineparser.cc
  Date      4/18/2019
  Author    Basil Elhindi
  Email     bae170000@utdallas.edu
  Course    CS 3377.502 Spring 2019
  Version   1.0
  Copyright 2019, All Rights Reserved

  Description
    C++ file that uses TCLAP to parse command line arguments, place them in a map for reference, and handle any errors and print the usage.
*/

#include <iostream>
#include <algorithm>
#include <tclap/CmdLine.h>
#include "header.h"

void parseCmdLine(int count, char* vals[])
{
  TCLAP::CmdLine cmd("CS 3377 Project5", ' ', "1.0");
  try{
    TCLAP::SwitchArg daemonArg("d", "daemon", "Run in daemon mode (forks to run as a daemon).", cmd, false);
    TCLAP::UnlabeledValueArg<string> configFileArg("configfilename", "The name of the configuration file. Defaults to dmd.conf.", false, "dmd.conf", "config filename", false);
    cmd.add(configFileArg);
    cmd.parse(count, vals);
    if(daemonArg.getValue())
      myMap[DAEMONARG] = "true";
    else myMap[DAEMONARG] = "false";
    myMap[CONFIGFILENAME] = configFileArg.getValue();
  }
  catch (TCLAP::ArgException &e)
  {
    cerr << "error: " << e.error() << " for arg " << e.argId() << endl;
    cmd.getOutput()->usage(cmd);
  }
}
