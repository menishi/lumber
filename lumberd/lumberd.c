#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "lumberd.h"

#define PORTNUM 1887


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


int main() {
  int pid = fork();
  if (pid == 0) {
    int sid = setsid();
    char msg[101];
  
    struct sockaddr_in dest;
    struct sockaddr_in serv;
    int mysocket;
    socklen_t socksize = sizeof(struct sockaddr_in);
  
    memset(&serv, 0, sizeof(serv));
  
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    serv.sin_port = htons(PORTNUM);
  
    mysocket = socket(AF_INET, SOCK_STREAM, 0);
    bind(mysocket, (struct sockaddr *)&serv, sizeof(struct sockaddr));
  
    listen(mysocket, 2);
    int consocket = accept(mysocket, (struct sockaddr *)&dest, &socksize);
    int len;
  
    while (consocket) {
      len = recv(consocket, msg, 100, 0);
      msg[len] = '\0';
      if (len > 0) printf("%s %d\n", msg, len);
      consocket = accept(mysocket, (struct sockaddr *)&dest, &socksize);
    }
    close(consocket);
    close(mysocket);
  }
  return EXIT_SUCCESS;
}
