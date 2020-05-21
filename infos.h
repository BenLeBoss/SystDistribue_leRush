#ifndef INFOS_H
#define INFOS_H

#include <stdio.h>


typedef struct
{
  int taille;
  int tableau[];
}tableau_entiers_t;

void set_taille(tableau_entiers_t tab,int t);

void set_tableau(tableau_entiers_t tab);

#endif
