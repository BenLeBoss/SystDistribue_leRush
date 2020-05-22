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


  static struct sockaddr_in adresse;
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

  sleep(5);

//  while(1){
    char buffer[20];
    int addrtaille = sizeof(ad_multicast);
    int nbytes = recvfrom(sock,buffer,30,0,(struct sockaddr *) &ad_multicast,&addrtaille);
    buffer[nbytes] = '\0';
    puts(buffer);
//  }


  return 0;
}
