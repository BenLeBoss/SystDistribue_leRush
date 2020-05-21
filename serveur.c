//#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
//#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


int main()
{

  //déclaration de la socket serveur
  struct sockaddr_in addr_server;
  struct sockaddr_in addr_client;
  char buffer[20];

  int socketServ = socket(AF_INET, SOCK_DGRAM, 0);
  if (socketServ == -1){
    perror("socket error\n");
    exit(1);
  }


  //liaison de la socket serveur sur le port voulu
  bzero(&addr_server, sizeof(struct sockaddr_in));
  addr_server.sin_family = AF_INET;
  addr_server.sin_port = htons(4000);
  addr_server.sin_addr.s_addr = htonl(INADDR_ANY);


  if (bind(socketServ, (const struct sockaddr*)&addr_server, sizeof(addr_server)) == -1){
    perror("bind error\n");
    exit(1);
  }
  printf("bind : %d\n", socketServ);

  //attente des données
  socklen_t lg = sizeof(struct sockaddr_in);
  int nb_octets = recvfrom(socketServ, buffer, 20, 0, (struct sockaddr*)&addr_client, &lg);
  if(nb_octets == -1){
    perror("reception error");
    exit(1);
  }

  buffer[nb_octets] = '\0';
  printf("Client : %s\n", buffer);

  close(socketServ);

  return 0;
}
