#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "infos.h"

int set_taille(tableau_entiers_t *tab,int t)
{
  tab->taille = t;
  return tab->taille;
}


void set_tableau(tableau_entiers_t *tab)
{
  //tab->tableau = (int*)malloc(2*sizeof(int));

    tab->tableau[0] = 4;
    tab->tableau[1] = 8;
    tab->tableau[2] = 12;
    tab->tableau[3] = 16;
    tab->tableau[4] = 20;

}


void set_port(configuration_t *config)
{
  config->port = 4000;
}


int set_hostname(configuration_t *config)
{
  char host[50];
  int val;
  val = gethostname(host, sizeof(host));
  if (val == -1){
    perror("Unable to get the hostname");
    return -1;
  }
  printf("hostname : %s\n", host);
  config->hostname = host;
  printf("hostname de la structure : %s\n\n", config->hostname);
  return 0;
}

// int main(){
//   configuration_t config;
//   set_port(&config);
//   set_hostname(&config);
//
//   tableau_entiers_t tab;
//   set_taille(&tab,5);
//   set_tableau(&tab);
//
//   printf("port du main : %d\nhostname du main : %s\n",config.port, config.hostname);
//   return 0;
// }
