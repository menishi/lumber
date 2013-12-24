#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "HistoryParser.h"

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

struct args *argproc(int argc, char *argv[]) {
  /***********************
   * Acceptable options:
   * NOTE: not all implemented yet. This is is to serve as a guide for direction.
   *  -f --file [FILENAME]       Specify a history file (~/.history used by default)
   *  -p --previous [NUMBER]     List last NUMBER of lines in current logfile.
   *  -d --date [YYMMDD-HHMM]    Specify dates to list history from. *
   *  -t --time [HHMM-HHMM]      Specify times to receive logs from.
   *  -a --all                   Specify all logs not just current.
   *  -l --log                   Specify a list of logs to use.
   *  -s --search                Search for entry in logs.
   *  -w --swap                  Change current log to a different one.
   *  -c --create                Create a new log.
   *  -m --move                  Move selected lines to selected logs.
   ***********************/  
  struct args *all = malloc(sizeof(struct args));
  int i;
  for (i = 1; i < argc; i++) {
    if (!strcmp(argv[i], "--last") || !strcmp(argv[i], "-l")) {
      all->lines = stringToInt(argv[++i]);
    } else if (!strcmp(argv[i], "--file") || !strcmp(argv[i], "-f")) {
      all->file = argv[++i];
    }
  }
  return all;
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

int main(int argc, char *argv[]) {
  struct args *all;
  all = argproc(argc, argv);
  struct fileAndLen *histFile = malloc(sizeof(struct fileAndLen));
  histFile->file = fopen(all->file, "r");
  histFile->length = countLines(histFile->file);
  char *line = malloc(sizeof(int)*100);
  printf("%s\n", getNthLineFromBottom(histFile, line, 4));
  return 0;
}
