#ifndef INFOS_H
#define INFOS_H

#include <stdio.h>


typedef struct
{
  int taille;
  int tableau[100];
}tableau_entiers_t;

typedef struct
{
  int port;
  char *hostname;
}configuration_t;

void set_taille(tableau_entiers_t *tab,int t);

void set_tableau(tableau_entiers_t *tab);

void set_port(configuration_t *config);

int set_hostname(configuration_t *config);

#endif
