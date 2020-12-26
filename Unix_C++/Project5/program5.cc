/*
  Filename  program5.cc
  Date      4/18/2019
  Author    Basil Elhindi
  Email     bae170000@utdallas.edu
  Course    CS 3377.502 Spring 2019
  Version   1.0
  Copyright 2019, All Rights Reserved

  Description
    C++ file containing main routine
*/

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <csignal>
#include <signal.h>
#include "header.h"

map<int,string> myMap;

void makePIDFile()
{
  ofstream pidfile;
  pidfile.open("dmd.pid");       
  pidfile << getpid();
  pidfile.close();
}

int main(int argc, char* argv[])
{
  cout << "Parsing command line" << endl;
  parseCmdLine(argc, argv);
  cout << "Reading configuration file" << endl;
  int success = configure();
  pid_t forkvalue;
  if(success == 0)
  {
    if(myMap[DAEMONARG] == "false")
    {
      cout << "Creating PID File" << endl;
      makePIDFile();
      cout << "Making .versions folder at WATCHDIR" << endl;
      string versionsfoldercmd = "mkdir -p " + myMap[WATCHDIR] + "/.versions";
      system(versionsfoldercmd.c_str());
      signal(SIGINT, signalHandle);
      signal(SIGHUP, signalHandle);
      cout << "Beginning log file at " << myMap[LOGFILE] << ". All output will be there." << endl;
      freopen(myMap[LOGFILE].c_str(), "a", stdout);
      int fw = folderWatch();
    }
    else
    {
       cout << "Forking process" << endl;
      forkvalue = fork();
      if(forkvalue == -1)
	cerr << "Error: fork() failed to create child" << endl;
      else if(forkvalue == 0)
      {
	cout << "Making PID file" << endl;
	makePIDFile();
	cout << "Making .versions folder at WATCHDIR" << endl;
	string versionsfoldercmd = "mkdir -p " + myMap[WATCHDIR] + "/.versions";
	system(versionsfoldercmd.c_str());
	signal(SIGINT, signalHandle);
	signal(SIGHUP, signalHandle);
	cout << "Beginning log file at " << myMap[LOGFILE] << ". All output will be there." << endl;
	freopen(myMap[LOGFILE].c_str(), "a", stdout);
        int fw = folderWatch();
      }
      else
      {
	//parent
      }
    }
  }
  else
  {
    cout << "Failed to configure" << endl;
  }
  return 0;
}
