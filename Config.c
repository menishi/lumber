#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lumberd/lumberd.h"
#include "Config.h"

/***********************
*  This file is part of Lumber.
*  
*  Lumber is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*  
*  Lumber is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*  
*  You should have received a copy of the GNU General Public License
*  along with Lumber.  If not, see <http://www.gnu.org/licenses/>.
*
*  Copyright 2013 Donal O'Shea
************************
*  This file is intended to be the log managment location.
*  It is supposed to contain all the details of managing the 
*  log directory and should not contain anything else.
***********************/


char *getConfig(int code) {
  char *home;
  switch (code) {
    case LUMBHOME:
      home = getenv("LUMBHOME");
      if (home) return home;
      else {
        home = malloc(sizeof(char)*100);
        strcat(home, getenv("HOME"));
        strcat(home,"/");
        strcat(home,".lumber/");
      }
      break;
    case DEFAULT_LOG:
      home = getLogPath("default");
      break;
    case HISTFILE:
      return getenv("HISTFILE");
  }
  return home;
} 

char *getLogPath(char *log) {
  char *home = getConfig(LUMBHOME);
  char *buffer = malloc(sizeof(char)*100);
  strcat(buffer, home);
  strcat(buffer,log);
  strcat(buffer,".lumb");
  return buffer;
}
