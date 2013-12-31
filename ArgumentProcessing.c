#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArgumentProcessing.h"
#include "main.h"

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

void envproc(struct args *all);

struct args *optproc(int argc, char *argv[]) {
  /***********************
   * Acceptable commands:
   *  create                     Create a new log.
   *  swap                       Change current log to a different one.
   *  search                     Search for entry in logs.
   *
   * NOTE: not all implemented yet. This is is to serve as a guide for direction.
   *  -f --file [FILENAME]       Specify a history file (~/.history used by default)
   *  -p --previous [NUMBER]     List last NUMBER of lines in current logfile.
   *  -d --date [YYMMDD-HHMM]    Specify dates to list history from. *
   *  -t --time [HHMM-HHMM]      Specify times to receive logs from.
   *  -a --all                   Specify all logs not just current.
   *  -l --log                   Specify a list of logs to use.
   *  -m --move                  Move selected lines to selected logs.
   ***********************/  

  struct args *all = malloc(sizeof(struct args));
  envproc(all);
  int i;
  all->lines = 0;
  for (i = 2; i < argc; i++) {
    if (!strcmp(argv[i], "--last") || !strcmp(argv[i], "-l")) {
      all->lines = stringToInt(argv[++i]);
    } else if (!strcmp(argv[i], "--file") || !strcmp(argv[i], "-f")) {
      all->file = argv[++i];
    }
  }

	if (all->file == NULL) {
	  all->file = strcat(all->home, "/.history");
	}
  return all;
}

void envproc(struct args *all) {
  all->home = getenv("HOME");
  if (!(logDirectory = getenv("LUMBHOME"))) {
      logDirectory = strcat(all->home, "/.lumber/");
  }
}

int cmdproc(int argc, char *argv[]) {
  if (argc < 3)
    return 0;
  if (!strcmp(argv[1], "create"))
    return 1;
  return 0;
}


int stringToInt(char* string) {
  int accum = 0;
  char * p = string;
  while (*p != '\0') {
    accum = accum * 10;
    accum += (int) *p -48;
    p++;
  }
  return accum;
}
