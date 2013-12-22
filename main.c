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
  if (strcmp(argv[1], "last") == 0) {
    printf("%d\n", stringToInt(argv[2]));
  }
  FILE *file = fopen("history","r");
  char *line = malloc(sizeof(int)*10);
  return 0;
}
