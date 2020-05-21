#include <stdio.h>

#include "infos.h"

void set_taille(tableau_entiers_t tab,int t)
{
  tab.taille = t;
}

void set_tableau(tableau_entiers_t tab)
{
  for (int i=0; i<=tab.taille; i++){
    tab.tableau[i] = i;
  }
}
