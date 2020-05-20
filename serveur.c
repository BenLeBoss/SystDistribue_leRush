#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//adresse privée : hostname -i
//adresse publique : hostname -I

int main(void)
{
  int socketServ = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in addrServ;
  addrServ.sin_addr.s_addr = inet_addr("127.0.1.1");
  addrServ.sin_family = AF_INET;
  addrServ.sin_port = htons(30000);

  bind(socketServ, (const struct sockaddr *)&addrServ, sizeof(addrServ));
  printf("bind : %d\n", socketServ);

  listen(socketServ, 5);
  printf("listen\n");

  struct sockaddr_in addrCl;
  socklen_t Clsize = sizeof(addrCl);
  int socketCl = accept(socketServ, (struct sockaddr *)&addrCl, &Clsize);
  printf("accept the connection\n");

  printf("client : %d\n", socketCl);

  int valeur=15;
  send(socketCl, &valeur, sizeof(valeur), 0);

  close(socketCl);
  close(socketServ);

  printf("close the server\n");

  return 0;
}
