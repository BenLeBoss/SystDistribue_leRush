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
#include "infos.h"
//gethostname -> récupère le nom de l'hote
//gethostbyname -> récupère les informations de l'hote avec son nom
//gethostbyaddr -> récupère les informations de l'hote avec son adresse
//inet_ntoa -> convertit une adresse en bits en adresse IPV4


int main(void)
{

  int nbClient=0;
  printf("Donner le nombre de clients attendus : ");
  scanf("%d", &nbClient);
  printf("En attente de \"%d\" clients\n", nbClient);

  //déclaration de la socket serveur
  int sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock == -1){
    perror("socket error\n");
    exit(1);
  }

  //autorise de lier plusieurs socket sur le port de l'ordi
  int reuse = 1;
  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (int *)&reuse, sizeof(reuse));

  //récupération adresse ip du groupe
  struct in_addr ip;
  inet_aton("226.1.2.3", &ip);

  //création de l'identificateur du groupe
  struct ip_mreq gr_multicast;
  gr_multicast.imr_multiaddr.s_addr = ip.s_addr;
  gr_multicast.imr_interface.s_addr = htons(INADDR_ANY);

  //abonnement de la socket au groupe multicast
  setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &gr_multicast, sizeof(struct ip_mreq));

  //Implémentation de la socket destinatrice
  static struct sockaddr_in ad_multicast;
  bzero((char*)&ad_multicast, sizeof(ad_multicast));
  ad_multicast.sin_family = AF_INET;
  ad_multicast.sin_addr.s_addr = htons(INADDR_ANY);
  ad_multicast.sin_port = htons(1234);
  bind(sock, (struct sockaddr*)&ad_multicast, sizeof(struct sockaddr_in));

  char buffer[50];
  //struct sockaddr *tableauClients[10];
  char *tableauClients[10];
  int port[10];

  //initialise la connecxion avec le client, récup son adresse et son port
  for(int i=0; i<nbClient; i++){
    int addrtaille = sizeof(ad_multicast);
    int nbytes = recvfrom(sock,buffer,30,0,(struct sockaddr*) &ad_multicast ,&addrtaille);
    //tableauClients[i]= (struct sockaddr*)&ad_multicast;
    tableauClients[i]=inet_ntoa(ad_multicast.sin_addr);
    port[i]=atoi(buffer);
    printf("Le port : %d\nL'adresse : %s\n", port[i], tableauClients[i]);
    buffer[nbytes] = '\0';
    puts(buffer);
  }


  //va chercher dans 2 tableaux l'adresse et le port d'un client, établie une connexion et envoie un message
  for(int j=0; j<nbClient; j++){
    int sockTCP = socket(AF_INET, SOCK_STREAM, 0);
    if (sockTCP == -1){
      perror("socket TCP error\n");
      exit(1);
    }

    struct hostent* host_serveur;
    struct in_addr addr;
    inet_aton((const char*)tableauClients[j],&addr);
    host_serveur = gethostbyaddr(&addr, sizeof(addr), AF_INET);
    if(host_serveur==NULL){
      perror("host serveur error");
      exit(1);
    }
    struct sockaddr_in addr_serveur;
    bzero((char*)&addr_serveur, sizeof(addr_serveur));
    addr_serveur.sin_family=AF_INET;
    addr_serveur.sin_port=htons(port[j]);
    memcpy(&addr_serveur.sin_addr.s_addr, host_serveur->h_addr, host_serveur->h_length);
    if (connect (sockTCP, (struct sockaddr*)&addr_serveur, sizeof(struct sockaddr_in)) == -1){
      perror("connect error");
      exit(1);
    }

    //écrit au client ------------à modifier par le tableau à envoyer
    int buffer[50];
    tableau_entiers_t tab;
    long tab1[50];
    int i,taille;
    set_tableau(&tab);
    taille= set_taille(&tab,5);
    int PartieTab[50];
    int b =0;
    int nbValeursADonnees=taille/nbClient;
    int indiceInf = 0;
    int indiceSup = nbValeursADonnees;
    for ( i = 1; i <= nbClient; i++) {
      /* code */

        if((nbClient ) == i){
          for(b=indiceInf; b<taille; b++){
            PartieTab[b]= tab.tableau[b];
          }
        }
        else{
          for(b=indiceInf; b<indiceSup; b++){
            PartieTab[b]= tab.tableau[b];
          }
          indiceInf = indiceSup;
          indiceSup+=nbValeursADonnees;
        }

        int octets2 = send(sockTCP, PartieTab, 50,0);

        b=0;

      }
    int nbytes = recv(sockTCP, tab1, 50,0);

    for (int j = 0; j <= (taille-1); j++) {
      printf("Factoriel de %d  : %ld \n",PartieTab[j],tab1[j]);
    }

    close(sockTCP);
  }


  //sûrement une 3e boucle pour reçevoir les données des clients





  // //Implémentation de la socket destinatrice
  // static struct sockaddr_in ad_multicast;
  // bzero((char*)&ad_multicast, sizeof(ad_multicast));
  // ad_multicast.sin_family = AF_INET;
  // ad_multicast.sin_addr.s_addr = htons(INADDR_ANY);
  // ad_multicast.sin_port = htons(1234);
  // bind(sock, (const struct sockaddr*)&ad_multicast, sizeof(struct sockaddr_in));

  // char buffer[50];
  // char *msg = "Connecté";
  // struct sockaddr *tableauClients[10];
  //
  // //les clients se connectent et le serveur leur répond
  // for(int i=0; i<nbClient; i++)
  // {
  //   int addrtaille = sizeof(ad_multicast);
  //   int nbytes = recvfrom(sock,buffer,30,0,(struct sockaddr*) &ad_multicast,&addrtaille);
  //   tableauClients[i]= (struct sockaddr*)&ad_multicast;
  //
  //   //connect(sock, (struct sockaddr*)&ad_multicast, addrtaille);
  //   buffer[nbytes] = '\0';
  //   puts(buffer);
  //   int nbites = sendto (sock, msg, strlen(msg)+1, 0, tableauClients[i], sizeof(ad_multicast));
  // }
  //
  // char *msg2 = "Futur tableau";
  // //write(sock, msg2, sizeof(msg2)+1);
  // for(int i=0; i<nbClient; i++){
  //   int nbites = sendto (sock, msg2, strlen(msg2)+1, 0, tableauClients[i], sizeof(ad_multicast));
  // }



  close(sock);
  return 0;
}
