#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORTNUM 1887

int server() {
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
    printf("Incoming connection from %s - recieving welcome\n", inet_ntoa(dest.sin_addr));
    len = recv(consocket, msg, 100, 0);
    msg[len] = '\0';
    if (len > 0) printf("%s %d\n", msg, len);
    consocket = accept(mysocket, (struct sockaddr *)&dest, &socksize);
  }
  close(consocket);
  close(mysocket);
  return EXIT_SUCCESS;
}

int main() {
  return server();
}
