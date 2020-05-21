//#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
//#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{

  //déclaration de la socket serveur
  struct sockaddr_in addr_server;
  struct sockaddr_in addr_client;

  int socketServ = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock == -1){
    error("socket error\n");
    return -1
  }


  //liaison de la socket serveur sur le port voulu
  bzero(&addr_server, sizeof(struct sockaddr_in));
  addr_server.sin_family = AF_INET;
  addr_server.sin_port = htons(4000);
  addr_server.sin_addr.s_addr = htonl(INADDR_ANY);


  if (bind(socketServ, (const struct sockaddr *)&addr_server, sizeof(addr_server)) == -1){
    perror("bind error\n");
    return -1;
  }

  //accueil 5 clients --> à changer
  listen(socketServ, 5);


  //déclaration de la socket client
  socklen_t Clsize = sizeof(addr_client);
  int socketCl = accept(socketServ, (struct sockaddr *)&addr_client, &Clsize);


  //fermeture des sockets serveur/clients
  close(socketCl);
  close(socketServ);

  return 0;
}
