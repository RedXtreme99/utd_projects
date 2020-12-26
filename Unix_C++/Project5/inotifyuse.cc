/*
  Filename  inotifyuse.cc
  Date      4/23/2019
  Author    Basil Elhindi
  Email     bae170000@utdallas.edu
  Course    CS 3377.502 Spring 2019
  Version   1.0
  Copyright 2019, All Rights Reserved

  Description
    File containing functions to implement inotify facilities to watch over a directory
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <linux/limits.h>
#include <sys/inotify.h>
#include "header.h"

#define BUFLEN sizeof(struct inotify_event) + PATH_MAX + 1

int folderWatch()
{
  int fd = inotify_init();
  if(fd < 0)
  {
    cout << "Error intializing inotify" << endl;
    return 1;
  }
  int wd;
  wd = inotify_add_watch(fd, myMap[WATCHDIR].c_str(), IN_MODIFY);
  if(wd == -1)
    cout << "Error adding watch" << endl;
  else cout << "Watching directory" << endl;
  struct inotify_event *event = (struct inotify_event *)malloc(BUFLEN);
  string datefilename;
  string date;
  string cpcmd;
  string mvcmd;
  while(1)
  {  
    read(fd, event, BUFLEN);
    if(event->len > 0)
      {
	cout << "Modified " << event->name << endl;
	cout << getLine() << endl;
	system(("cp " + myMap[WATCHDIR] + "/" +  string(event->name) + " " +  myMap[WATCHDIR] + "/.versions/" + event->name + getLine()).c_str());
      }
  }  
  return 0;
}
