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

  //déclaration de la socket
  struct sockaddr_in addr_server;
  int socket = socket(AF_INET, SOCK_DGRAM, 0);
  if (socket == -1){
    error("socket error\n");
    return -1
  }

  //récupération de l'identifiant du serveur
  char hostname[50];
  int val;
  val = gethostname(hostname, sizeof(hostname));
  if (val == -1){
    perror("Unable to get the hostname");
    return -1;
  }

  struct hostent *serveur_host;
  serveur_host = gethostbyname(hostname);


  //création de la socket du serveur
  bzero(&addr_server, sizeof(struct sockaddr_in));
  addr_server.sin_family = AF_INET;
  addr_server.sin_port = htons(4000);
  memcpy(&addr_cserver.sin_addr.s_addr, serveur_host->h_addr, serveur_host->h_length);


  close(socket);

  return 0;
}
