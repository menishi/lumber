#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "lumberd.h"
#include <regex.h>
#include "../Config.h"

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

#define PORTNUM 31887

void *startNetwork(void *args) {
  // Message from network container
  char msg[101];
  struct NetworkData *data = (struct NetworkData*)args;
  
  struct sockaddr_in dest;
  struct sockaddr_in serv;
  int listenSocket = 0, connSocket = 0;
  socklen_t socksize = sizeof(struct sockaddr_in);

  memset(&serv, 0, sizeof(serv));

  serv.sin_family = AF_INET;
  serv.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  serv.sin_port = htons(PORTNUM);

  // Bind to the listen socket
  listenSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (listenSocket < 0) {
    data->netStatus = LISTEN_SOCKET_BIND_ERROR;
    return data;
  }
  bind(listenSocket, (struct sockaddr *)&serv, sizeof(struct sockaddr));

  if (listen(listenSocket, 10) < 0)  {
    data->netStatus = LISTEN_ERROR;
    return data;
  }

  connSocket = accept(listenSocket, (struct sockaddr *)&dest, &socksize);
  int len;

  while (TRUE) {
    if (connSocket != -1) {
      len = recv(connSocket, msg, 100, 0);
      msg[len] = '\0';
      if (len > 0) {
        strcpy(data->mode, msg);
        break;
      }
    }
    connSocket = accept(listenSocket, (struct sockaddr *)&dest, &socksize);
  }
  close(connSocket);
  close(listenSocket);
  data->netStatus = NETWORK_SUCCESS;
  return data;
}

void msgProc(struct LogState *lst, struct NetworkData *data) {
  regex_t regex;
  int reti;
  reti = regcomp(&regex, "switch .*", 0);
  reti = regexec(&regex, data->mode, 0, NULL, 0);
  char *passer = data->mode;
  if (!reti) {
    lst->cmd = 2;
    while (*passer != ' ') passer++;
    lst->currentLog.path = getLogPath(passer);
    lst->currentLog.file = fopen(lst->currentLog.path, "r");
  }
  regfree(&regex);
}
