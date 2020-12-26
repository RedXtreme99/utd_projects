/*
  Filename  signalHandler.cc
  Date      4/23/19
  Author    Basil Elhindi
  Email     bae170000@utdallas.edu
  Course    CS 3377.502 Spring 2019
  Version   1.0
  Copyright 2019, All Rights Reserved

  Description
    C++ file meant to handle signals that the daemon recieves.
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "header.h"

void signalHandle(int sig)
{
  cout << "\nSignal " << sig << " received" << endl;
  if(myMap[VERBOSE] == "true")
    for(int i = 0; i <= WATCHDIR; i++)
      cout << myMap[i] << endl;
  if(sig == 1)
  {
    cout << "SIGHUP" << endl;
    if(configure() == 1)
      cout << "Error reconfiguring" << endl;
    else cout << "Reconfigured" << endl;
    if(myMap[VERBOSE] == "true")
      for(int i = 0; i <= WATCHDIR; i++)
	cout << myMap[i] << endl;
  }  
  if(sig == 2 || sig == 15)
  {
    cout << "SIGINT" << endl;
    cout << "Removing PID file" << endl;
    system("rm -f dmd.pid");
    cout << "Closing log file and closing the process" << endl;
    fclose(stdout);
    exit(0);
  }
}
