#pragma once

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

#define ARGUMENT_ERROR 2
#define FILE_ERROR 3
#define LOG_EXISTS_ERROR 4
#define INVALID_LOG_ERROR 5

char *logDirectory;

struct args {
  char* file;
  char *home;
  int lines;
};

struct fileAndLen {
  FILE *file;
  int length;
};
