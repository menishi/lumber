#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
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
  int returnCode = 0;
  struct args *all;
  char *logFilePath;
  FILE *log;

  all = optproc(argc, argv);  // This extracts our options

  struct fileAndLen *histFile = malloc(sizeof(struct fileAndLen));
  histFile->file = fopen(all->file, "r");
  histFile->length = countLines(histFile->file);

  int n;
  char *line = malloc(sizeof(int)*100);

  int cmdCode = cmdproc(argc, argv);
  switch(cmdCode)  {
    case 0:
      fprintf(stderr, "Error incorrect arguments. Usage: lumber command options\n");
      returnCode = ARGUMENT_ERROR;
      break;
    
    case 1:                                                            // 1 for a create statement
      logFilePath = pathToFile(logDirectory,argv[2]);
      if (access(logFilePath, F_OK) != -1) {
        fprintf(stderr, "ERROR: log \"%s\" already exists\n", argv[2]);
        returnCode =  LOG_EXISTS_ERROR;
      }
      log = fopen(logFilePath, "w");
      if (!log) {
        fprintf(stderr, "ERROR: file could not be opened\n");
        returnCode = FILE_ERROR;
      }

      break;

    case 2:                                                            // 2 for a switch statement
      logFilePath = pathToFile(logDirectory, argv[2]);
      if (access(logFilePath, F_OK) == -1) {
        fprintf(stderr, "ERROR: log \"%s\" does not exist\n", argv[2]);
        return INVALID_LOG_ERROR;
      }
      log = fopen(logFilePath, "a");
      if (!log) {
        fprintf(stderr, "ERROR: file could not be opened\n");
        returnCode =  FILE_ERROR;
      }

      break;
  }
  if (cmdCode == 1 || cmdCode == 2) {
    for (n = all->lines;n >=0; n--) {                                // This component takes the last n lines 
      fprintf(log, "%s\n", getNthLineFromBottom(histFile, line, n)); // from the history file and enters it into the
    }                                                                // log file
  }
  return returnCode;
}
