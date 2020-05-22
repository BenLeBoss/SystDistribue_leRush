#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

//gethostname -> récupère le nom de l'hote
//gethostbyname -> récupère les informations de l'hote avec son nom
//gethostbyaddr -> récupère les informations de l'hote avec son adresse
//inet_ntoa -> convertit une adresse en bits en adresse IPV4


int main(void)
{

  configuration_t config;
  set_port(&config);
  set_hostname(&config);
  tableau_entiers_t tab;
  set_taille(&tab,5);
  set_tableau(&tab);

  //déclaration de la socket
  struct sockaddr_in addr_server;
  int socketS = socket(AF_INET, SOCK_DGRAM, 0);
  if (socketS == -1){
    perror("socket error\n");
    exit(1);
  }

  //récupération de l'identifiant du serveur
  char hostname[50];
  int val;
  val = gethostname(hostname, sizeof(hostname));
  if (val == -1){
    perror("Unable to get the hostname");
    exit(1);
  }

  struct hostent *serveur_host;
  serveur_host = gethostbyname(hostname);
  printf("hostname : %s\n", hostname);


  //création de la socket du serveur
  bzero(&addr_server, sizeof(struct sockaddr_in));
  addr_server.sin_family = AF_INET;
  addr_server.sin_port = htons(4000);
  memcpy(&addr_server.sin_addr.s_addr, serveur_host->h_addr, serveur_host->h_length);

  //envoie un message
  char *msg = "bonjour";
  socklen_t lg = sizeof(struct sockaddr_in);
  int nb_octets = sendto (socketS, msg, strlen(msg)+1, 0, (struct sockaddr*)&addr_server, lg);
  if (nb_octets == -1){
    perror("send error");
    exit(1);
  }
  printf("msg \"%s\" envoyé, nb_octets = %d\n", msg, nb_octets);


  close(socketS);

  return 0;
}
