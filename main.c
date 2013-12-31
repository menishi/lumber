#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "main.h"
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
  all = optproc(argc, argv);
  switch (cmdproc(argc, argv)) {
    case 0:
      all = NULL;
      break;
    // 1 for a create statement
    case 1:
      log = fopen(strcat(logDirectory, argv[2]), "a");
      break;
  }
  if (all == NULL){
    fprintf(stderr, "Error incorrect arguments. Usage: lumber command options\n");
    return 2;
  }

  // histFile is where we store the main history file created by bash/zsh
  struct fileAndLen *histFile = malloc(sizeof(struct fileAndLen));
  histFile->file = fopen(all->file, "r");
  histFile->length = countLines(histFile->file);

  int n;
  char *line = malloc(sizeof(int)*100);
  for (n = all->lines;n >=0; n--) {
    printf("%s\n", parseHistoryLine(getNthLineFromBottom(histFile, line, n)));
  }
  return 0;
}
