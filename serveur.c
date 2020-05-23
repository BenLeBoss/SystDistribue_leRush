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

  int nbClient=0;
  printf("Donner les nombre de clients attendus : ");
  scanf("%d", &nbClient);
  printf("En attente de \"%d\" clients\n", nbClient);

  struct in_addr ip;

  //déclaration de la socket serveur
  int sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock == -1){
    perror("socket error\n");
    exit(1);
  }

  //autorise de lier plusieurs socket sur le port de l'ordi
  int reuse = 1;
  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (int *)&reuse, sizeof(reuse));


  //liaison de la socket au port du groupe multicast
  static struct sockaddr_in ad_multicast;
  bzero((char*)&ad_multicast, sizeof(ad_multicast));
  ad_multicast.sin_family = AF_INET;
  ad_multicast.sin_addr.s_addr = htons(INADDR_ANY);
  ad_multicast.sin_port = htons(1234);
  bind(sock, (const struct sockaddr*)&ad_multicast, sizeof(struct sockaddr_in));

  //récupération adresse ip du groupe
  inet_aton("226.1.2.3", &ip);

  //création de l'identificateur du groupe
  struct ip_mreq gr_multicast;
  gr_multicast.imr_multiaddr.s_addr = ip.s_addr;
  gr_multicast.imr_interface.s_addr = htons(INADDR_ANY);

  //abonnement de la socket au groupe multicast
  setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &gr_multicast, sizeof(struct ip_mreq));

  unsigned char ttl = 255;
  setsockopt(sock, IPPROTO_IP, IP_MULTICAST_TTL, &ttl, sizeof(ttl));

  char buffer[50];
  char *msg = "Connecté";

  for(int i=0; i<nbClient; i++)
  {
    int addrtaille = sizeof(ad_multicast);
    int nbytes = recvfrom(sock,buffer,30,0,(struct sockaddr*) &ad_multicast,&addrtaille);
    buffer[nbytes] = '\0';
    puts(buffer);
    int nbites = sendto (sock, msg, strlen(msg)+1, 0, (struct sockaddr*)&ad_multicast, sizeof(ad_multicast));
  }

  close(sock);
  return 0;
}
