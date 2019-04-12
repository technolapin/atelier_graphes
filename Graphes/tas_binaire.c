#include <stdlib.h>
#include <stdio.h>
#include "graphaux.h"
#include "graphes.h"

#include "tas_binaire.h"



tas_binaire
cree_tas(void)
{
  return NULL;
}

int
tas_est_vide(tas_binaire tas)
{
  return tas == NULL;
}

void
ajoute_sommet(tas_binaire *tas, graphe * g, int i)
{
  if (*tas == NULL)
  { 
    noeud_tas_binaire *
      noeud = (noeud_tas_binaire *) malloc(sizeof(noeud_tas_binaire));
    noeud->sommet = i;
    noeud->gauche = NULL;
    noeud->droite = NULL;
   *tas = noeud;
    return;
  }
  
  int j = (*tas)->sommet;
  if (g->v_sommets[i] < g->v_sommets[j] && g->v_sommets[i] != -1 || g->v_sommets[j]==-1)
    ajoute_sommet(&(*tas)->gauche, g, i);
  else
    ajoute_sommet(&(*tas)->droite, g, i);
    
}

void
affiche_tas(tas_binaire tas)
{
  if (tas == NULL)
    printf("NULL");
  else
    {
      printf("(");
      affiche_tas(tas->gauche);
      printf(" %d ", tas->sommet);
      affiche_tas(tas->droite);
      printf(")");
    }
}

void
affiche_tas_poids(tas_binaire tas, graphe* g)
{
  if (tas == NULL)
    printf("NULL");
  else
    {
      int v = (g->v_sommets)[tas->sommet];
      printf("(");
      affiche_tas_poids(tas->gauche, g);
      printf(" %d ", v);
      affiche_tas_poids(tas->droite, g);
      printf(")");
    }
}




void
libere_tas(tas_binaire tas)
{
  if (tas!=NULL)
  {
    if (tas->gauche != NULL)
      libere_tas(tas->gauche);
    if (tas->droite != NULL)
      libere_tas(tas->droite);
    free(tas);
  }
}


int
minimum_tas(tas_binaire tas)
{
  if (tas == NULL)
    return -1;
  else
    if (tas->gauche)
      return minimum_tas(tas->gauche);
    else
      return tas->sommet;
}


int
maximum_tas(tas_binaire tas)
{
  if (tas == NULL)
    return -1;
  else
    if (tas->droite)
      return maximum_tas(tas->droite);
    else
      return tas->sommet;
}


int pop_max(tas_binaire *tas)
{
  if (*tas == NULL)
    return -1;
  else
    if ((*tas)->droite)
      return pop_max(&(*tas)->droite);
    else
    {
      int i = (*tas)->sommet;
      free(*tas);
      if ((*tas)->gauche)
	*tas = (*tas)->gauche;
      else
	*tas = NULL;
      return i;
    }
}
int pop_min(tas_binaire *tas)
{
  if (*tas == NULL)
    return -1;
  else
    if ((*tas)->gauche)
      return pop_min(&(*tas)->gauche);
    else
    {
      int i = (*tas)->sommet;
      free(*tas);
      if ((*tas)->droite)
	*tas = (*tas)->droite;
      else
	*tas = NULL;
      return i;
    }
}

int
pop_tas(tas_binaire *tas)
{
  if (*tas == NULL)
    return -1;
  int i = (*tas)->sommet;
  if ((*tas)->gauche == NULL)
  {
    free(*tas);
    *tas = (*tas)->droite;
  }
  else if ((*tas)->droite == NULL)
  {
    free(*tas);
    *tas = (*tas)->gauche;
  }
  else
    (*tas)->sommet = pop_max(&(*tas)->gauche);

  return i;
}





