#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lumber.h"

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

char *getIdentifierFromLine(char *line);
int countLines(FILE *file);
char *getNthLine(FILE *file, char* line, int n);
char *getNthLineFromBottom(FILE *file, char* line, int n);
char *parseHistoryLine(char *line);
char *getLine(FILE *file, char *line);
int getLineNumberWithIdent(FILE *file, char *ident);
