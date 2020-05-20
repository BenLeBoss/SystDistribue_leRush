#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//gethostname -> récupère le nom de l'hote
//gethostbyname -> récupère les informations de l'hote avec son nom
//gethostbyaddr -> récupère les informations de l'hote avec son adresse
//inet_ntoa -> convertit une adresse en bits en adresse IPV4


int main(void)
{



  int socketCl = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in addrCl;
  addrCl.sin_addr.s_addr = inet_addr("127.0.1.1");
  addrCl.sin_family = AF_INET;
  addrCl.sin_port = htons(30000);

  connect(socketCl, (const struct sockaddr *)&addrCl, sizeof(addrCl));
  printf("connecté\n");

  int valeur = 0;
  recv(socketCl, &valeur, sizeof(int), 0);
  printf("La valeur reçue est : %d\n", valeur);

  close(socketCl);

  return 0;
}
