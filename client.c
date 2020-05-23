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

int main()
{


  struct in_addr ip;

  //déclaration de la socket serveur
  int sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock == -1){
    perror("socket error\n");
    exit(1);
  }

  //autorise de lier plusieurs socket sur le port de l'ordi
  //int reuse = 1;
  //setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (int *)&reuse, sizeof(reuse));


  //liaison de la socket au port du groupe multicast
  static struct sockaddr_in ad_multicast;
  bzero((char*)&ad_multicast, sizeof(ad_multicast));
  ad_multicast.sin_family = AF_INET;
  ad_multicast.sin_addr.s_addr = htons(INADDR_ANY);
  ad_multicast.sin_port = htons(1234);
  bind(sock, (const struct sockaddr*)&ad_multicast, sizeof(struct sockaddr_in));

  //récupération adresse ip du groupe
//inet_aton("226.1.2.3", &ip);

  //création de l'identificateur du groupe
  // struct ip_mreq gr_multicast;
  // gr_multicast.imr_multiaddr.s_addr = ip.s_addr;
  // gr_multicast.imr_interface.s_addr = htons(INADDR_ANY);

  //abonnement de la socket au groupe multicast
  //setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &gr_multicast, sizeof(struct ip_mreq));


  //envoie de paquets
  char *msg = "Un client se connecte";
  int nbytes = sendto (sock, msg, strlen(msg)+1, 0, (struct sockaddr*)&ad_multicast, sizeof(ad_multicast));

  //réponse du serveur
  struct sockaddr_in adresse;
  char buffer[50];
  int addrtaille = sizeof(ad_multicast);
  int nbites = recvfrom(sock,buffer,100,0,(struct sockaddr*)&ad_multicast, &addrtaille);
  buffer[nbites] = '\0';
  printf("Confirmation que le serveur a reçu et renvoyé : ");
  puts(buffer);

  close(sock);
}
