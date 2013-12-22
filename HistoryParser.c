#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

char *getLine(FILE *file, char* line) {
  char *start = line;
  while ((*line = fgetc(file)) && *line != '\n')
    line++;
  *line = '\0';
  return start;
}

char *parseHistoryLine(char* line) {
 char *c;
 c = &*line;
 int afterColon = 0;
 char *strCmd = malloc(sizeof(char)*200);
 char *pointIt = strCmd;
 while (*c != '\0') {
   if (afterColon) {
     *pointIt = *c;
     pointIt++;
   }
   if (*c == ';') afterColon = 1;
   c++;
 }
 *pointIt = '\0';
 return strCmd;
} 
