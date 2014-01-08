#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lumber.h"
#include "ArgumentProcessing.h"
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

int main(int argc, char *argv[]) {
  struct args *all;
  FILE *log;
  // Extract any options from the command line
  all = optproc(argc, argv);

  struct fileAndLen *histFile = malloc(sizeof(struct fileAndLen));
  histFile->file = fopen(all->file, "r");
  histFile->length = countLines(histFile->file);

  int n;
  char *line = malloc(sizeof(int)*100);


  // Here is our main command processing loop
  switch (cmdproc(argc, argv)) {
    // This is our error catch
    case 0:
      all = NULL;
      break;
    // 1 for a create statement
    case 1:
      log = fopen(pathToFile(logDirectory,argv[2]), "a");
      if (!log) {
        fprintf(stderr, "Error, file could not be opened\n");
        return FILE_ERROR;
      }

      // This component takes the last n lines from the history file and enters it into the
      // log file
      for (n = all->lines;n >=0; n--) {
        fprintf(log, "%s\n", getNthLineFromBottom(histFile, line, n));
      }
      break;
  }

  if (all == NULL){
    fprintf(stderr, "Error incorrect arguments. Usage: lumber command options\n");
    return ARGUMENT_ERROR;
  }
  // histFile is where we store the lumber.history file created by bash/zsh
  return 0;
}
