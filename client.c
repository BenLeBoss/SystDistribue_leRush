#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include "infos.h"

int main()
{

  //PARTIE UDP
  //déclaration de la socket udp
  int sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock == -1){
    perror("socket UDP error\n");
    exit(1);
  }

  struct in_addr ip;
  inet_aton("226.1.2.3", &ip);

  //création de l'identificateur du groupe
  struct ip_mreq gr_multicast;
  gr_multicast.imr_multiaddr.s_addr = ip.s_addr;
  gr_multicast.imr_interface.s_addr = htons(INADDR_ANY);

  //autorise de lier plusieurs socket sur le port de l'ordi
  int reuse = 1;
  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (int *)&reuse, sizeof(reuse));

  //Implémentation de la socket destinatrice
  static struct sockaddr_in ad_multicast;
  bzero(&ad_multicast, sizeof(ad_multicast));
  ad_multicast.sin_family = AF_INET;
  ad_multicast.sin_addr.s_addr =  gr_multicast.imr_multiaddr.s_addr;
  ad_multicast.sin_port = htons(1234);


  //PARTIE TCP
  int sockTCP_ecoute = socket(AF_INET, SOCK_STREAM, 0);
  if (sockTCP_ecoute == -1){
    perror("socket TCP error\n");
    exit(1);
  }

  //demande un port pour que les clients en aient des différents
  int port = 0;
  printf("Donner un numéro de port non attribué (30 000, 40 0000 ou 50 000 par exemple) : ");
  scanf("%d", &port);

  static struct sockaddr_in addr_serveur;
  bzero((char*)&addr_serveur, sizeof(struct sockaddr_in));
  addr_serveur.sin_family = AF_INET;
  addr_serveur.sin_port = htons(port);
  addr_serveur.sin_addr.s_addr = htonl(INADDR_ANY);
  if (bind(sockTCP_ecoute, (struct sockaddr*)&addr_serveur, sizeof(addr_serveur)) == -1){
    perror(" bind sockTCP ecoute error");
    exit(1);
  }

  //envoie le port au serveur
  char buffer[50];
  sprintf(buffer, "%d", port);
  int lg = sizeof(struct sockaddr_in);
  int nb_octets = sendto(sock, buffer, 50,0,(struct sockaddr*)&ad_multicast, lg);


  //attend une connexion tcp (réponse du serveur)
  if (listen(sockTCP_ecoute, 3) == -1){
    perror("listen error");
    exit(1);
  }

  //accepte la connexion
  static struct sockaddr_in addr_client;
  int lg_addr = sizeof(struct sockaddr_in);
  int socketTCP_service = accept(sockTCP_ecoute, (struct sockaddr*)&addr_client, &lg_addr);
  if (socketTCP_service == -1){
    perror("socket TCP error\n");
    exit(1);
  }

  //en attente de messages et affiche -------à modif reçoit le tableau
  int tableau[50];
  int nbytes = recv(socketTCP_service, tableau, sizeof(tableau),0);

  int k = 0;
  while (tableau[k]!=0){
    printf("%d\n", tableau[k]);
    k++;
  }
  //à modif
  long tab1[50];
  int i,j;
  long resultat;
  for (i=0;  i< k;i++){
      resultat =1;
      for (j = 1; j <= tableau[i]; j++) {
        resultat = resultat*j;
      }
      tab1[i] = resultat;
  }
  int octets = send(socketTCP_service, tab1, sizeof(tab1),0);


  //à rajouter le client qui renvoie le tableau au serveur

  close(sock);

}
