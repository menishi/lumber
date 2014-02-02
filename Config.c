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
***********************/

char *getConfig(int code) {
  char *home = getenv("LUMBHOME");
  char *buffer = malloc(sizeof(char)*100);
  switch (code) {
    case DEFAULT_LOG:
      if (!home) {
        strcat(buffer, getenv("HOME"));
      home = strcat(buffer, "/.lumber/default.lumb");
      }
      break;
  }
  return home;
} 

int main() {
  getConfig(0);
  return 0;
}
