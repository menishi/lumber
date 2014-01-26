#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>


#define MAXREC 100
#define PORTNUM 1887

int getMessage() {
  char buffer[] = "Hello Fish!";
  int len, mysocket;
  struct sockaddr_in dest;

  mysocket = socket(AF_INET, SOCK_STREAM, 0);

  memset(&dest, 0, sizeof(dest));
  dest.sin_family = AF_INET;
  dest.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  dest.sin_port = htons(PORTNUM);

  connect(mysocket, (struct sockaddr *)&dest, sizeof(struct sockaddr));
  printf("%s\n", buffer);
  write(mysocket,buffer, strlen(buffer));


  close(mysocket);
  return EXIT_SUCCESS;
}

int main() {
  return getMessage();
}
