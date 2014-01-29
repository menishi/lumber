#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "Networking.h"
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

#define MAXREC 100
#define PORTNUM 1887

int sendMessage(char *msg) {
  int len, mysocket;
  struct sockaddr_in dest;

  if ((mysocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    return SOCK_CREATE_ERROR;
  memset(&dest, 0, sizeof(dest));
  dest.sin_family = AF_INET;
  dest.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  dest.sin_port = htons(PORTNUM);

  int r = connect(mysocket, (struct sockaddr *)&dest, sizeof(struct sockaddr));
  if (r < 0) 
    return CON_FAIL_ERROR;
  if (write(mysocket, msg, strlen(msg)) < 0) 
    return WRITE_FAIL_ERROR;

  close(mysocket);
  return EXIT_SUCCESS;
}
