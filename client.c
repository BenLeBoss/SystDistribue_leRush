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
  struct ip_mreq gr_multicast;

  //déclaration de la socket serveur
  int sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock == -1){
    perror("socket error\n");
    exit(1);
  }

  //liaison de la socket au port du groupe multicast
  static struct sockaddr_in adresse;
  bzero((char*)&adresse, sizeof(adresse));
  adresse.sin_family = AF_INET;
  adresse.sin_addr.s_addr = htons(INADDR_ANY);
  adresse.sin_port = htons(1234);
  bind(sock, (const struct sockaddr*)&adresse, sizeof(struct sockaddr_in));


  //envoie de paquets
  char *msg = "yoooo";
 //while(1){
   char ch = 0;
   int nbytes = sendto (sock, msg, strlen(msg)+1, 0, (struct sockaddr*)&adresse, sizeof(adresse));

 //}


  close(sock);


  return 0;
}
