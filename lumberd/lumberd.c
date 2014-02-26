#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "Network.h"
#include "../Config.h"
#include "lumberd.h"

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

// 1. Add initial conditions for machine state
// 2. Clean up startNetwork procedure
// 3. Define the msgProc function
// 4. Add memory freeing for everything

int main() {
  int pid = fork();
  if (pid != 0) {
    int sid = setsid();

    struct LogState lst;

    struct NetworkData data;
    data.mode = malloc(sizeof(char)*100);
    data.currentLog = malloc(sizeof(char)*100);
    lst.currentLog.path = getConfig(DEFAULT_LOG);
    lst.currentLog.file = fopen(lst.currentLog.path, "r");
    lst.histFile.path = getConfig(DEFAULT_LOG);
    lst.histFile.file = fopen(lst.histFile.path, "r");

    pthread_t pth;
    pthread_create(&pth, NULL, startNetwork, &data);

    while (1) {
      // This is to avoid eating up to much proccessor power
      usleep(20000);
      msgProc(&lst, &data);

      switch (lst.cmd) {
        case KILL_COMMAND:
          return KILL_RECEIVED;
        case SWITCH_COMMAND:
        default:
          break;
      }
    }

    pthread_join(pth, NULL);

    free(data.currentLog);
    free(data.mode);
   }
  return EXIT_SUCCESS;
}
