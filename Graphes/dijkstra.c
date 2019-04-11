#include <stdlib.h>
#include <stdio.h>
#include "graphaux.h"
#include "graphes.h"


#define USAGE "dijkstra <filel>"


graphe * Sym(graphe * g)
{
  graphe *g_1;
  int nsom, narc, k, i, j;
  pcell p;

  nsom = g->nsom;
  narc = g->narc;
  g_1 = InitGraphe(nsom, narc);

  for (i = 0; i < nsom; i++)
  {
    g_1->v_sommets[i] = g->v_sommets[i];

    for (p = g->gamma[i]; p != NULL; p = p->next)
    {
      AjouteArcValue( g_1,
		      p->som,
		      i,
		      p->v_arc );
    }
  }
  
  return g_1;
} /* Sym() */


void Dijkstra(graphe * g, int i)
{
  int nsom, narc, k, x, y, j;
  pcell p;
  nsom = g->nsom;
  narc = g->narc;
  long int* pi = g->v_sommets; // parce que c'est plus sympa à taper
  long int* s = (long int*) malloc(nsom*sizeof(long int));
  long int x_min;
  

  for (int som = 0;
       som < nsom;
       som++ )
  {
    pi[som] = -1; // on va dire que +inf = -1
  }
  pi[i] = 0;
  s[i] = 1;

  k = 1;
  x = i;
  
  while (k < nsom && pi[x] != -1)
  {
    for (p = g->gamma[x]; p != NULL; p = p->next) 
    {
      y = p->som;

      if (s[y] == 0 )
      {
      
	int sum = pi[x] + p->v_arc;  //poid en x + celui de l'arc
	if (pi[y] < 0 || pi[y] >= sum)
	  pi[y] = sum;
      }
      
    }
    
    x_min = x;
    for (y = 0; y < nsom; y++)
    {
      if ( !s[y] && pi[y] >= 0 &&
	   (pi[y] < pi[x_min] || s[x_min])  )
      {
	x_min = y;
      }
    }
    s[x] = 1;
    x = x_min;

    
    k++;
  }
    
  free(s);
}

char  *
Dijkstra_eco(graphe * g, int i, int but)
{
  int nsom, narc, k, x, y, j;
  pcell p;
  nsom = g->nsom;
  narc = g->narc;
  long int* pi = g->v_sommets; // parce que c'est plus sympa à taper
  char* s = (char*) malloc(nsom*sizeof(char));
  long int x_min;
  

  for (int som = 0;
       som < nsom;
       som++ )
  {
    pi[som] = -1; // on va dire que +inf = -1
  }
  pi[i] = 0;
  s[i] = 1;

  k = 1;
  x = i;
  
  while (k < nsom && pi[x] != -1)
  {
    for (p = g->gamma[x]; p != NULL; p = p->next) 
    {
      y = p->som;

      if (s[y] == 0 )
      {
      
	int sum = pi[x] + p->v_arc;  //poid en x + celui de l'arc
	if (pi[y] < 0 || pi[y] >= sum)
	  pi[y] = sum;
      }
      
    }
    
    x_min = x;
    for (y = 0; y < nsom; y++)
    {
      if ( !s[y] && pi[y] >= 0 &&
	   (pi[y] < pi[x_min] || s[x_min])  )
      {
	x_min = y;
      }
    }
    s[x] = 1;
    if (x == but)
      return s;
    
    x = x_min;

    
    k++;
  }
  return s;
  //  free(s);
}




double
heuristic_dist(graphe * g, int i, int j)
{
  double dx = g->x[i] - g->x[j];
  double dy = g->y[i] - g->y[j];
  if (dx < 0)
    dx = -dx;
  if (dy < 0)
    dy = -dy;
  return dx+dy;
}

long
heuristic(graphe * g, int x, int but, int coeff)
{
  double d = heuristic_dist(g, x, but);
  return g->v_sommets[x]+ floor(d)*coeff;
}


char *
A_star(graphe * g, int i, int but, int coeff)
{
  int nsom, narc, k, x, y, j;
  pcell p;
  nsom = g->nsom;
  narc = g->narc;
  long int* pi = g->v_sommets; // parce que c'est plus sympa à taper
  char* s = (char*) malloc(nsom*sizeof(char));
  long int x_min;
  

  for (int som = 0;
       som < nsom;
       som++ )
  {
    pi[som] = -1; // on va dire que +inf = -1
  }
  pi[i] = 0;
  s[i] = 1;

  k = 1;
  x = i;
  
  while (k < nsom && pi[x] != -1)
  {
    for (p = g->gamma[x]; p != NULL; p = p->next) 
    {
      y = p->som;

      if (s[y] == 0 )
      {
      
	int sum = pi[x] + p->v_arc;  //poid en x + celui de l'arc
	if (pi[y] < 0 || pi[y] >= sum)
	  pi[y] = sum;
      }
      
    }
    
    x_min = x;
    long v_min = heuristic(g, x, but, coeff);
    long v_min_1;
    for (y = 0; y < nsom; y++)
    {
      v_min_1 = heuristic(g, y, but, coeff);
      printf("%d %d %d %d \n", x_min, y, v_min, v_min_1);
      if ( !s[y] && pi[x] >= 0 &&
	   (v_min_1 < v_min || s[x_min]) && pi[y] >= 0 )
      {
	x_min = y;
	v_min = v_min_1;
      }
    }
    s[x] = 1;
    if (x == but)
      return s;
    
    x = x_min;

    
    k++;
  }
  return s;
}


graphe *
deep_copy(graphe * g)
{
  long int nsom, narc;
  int i, j, k;
  graphe * g_1;
  pcell p;

  nsom = g->nsom;
  narc = g->narc;
  g_1 = InitGraphe(nsom, narc);

  g_1->nomsommet = (char **)malloc(nsom * sizeof(char *));

  
  for (i=0; i < nsom; i++)
  {
    g_1->nomsommet[i] = (char*)malloc((strlen(g->nomsommet[i])+1) * sizeof(char));
    for (j = 0; g->nomsommet[i][j] != 0; j++) 
      g_1->nomsommet[i][j] = g->nomsommet[i][j];
    g_1->nomsommet[i][j] = 0;

    g_1->x[i] = g->x[i];
    g_1->y[i] = g->y[i];

    k = 0;
    for (p = g->gamma[i]; p != NULL; p = p->next)
    {
      j = p->som;
      g_1->queue[k] = i;
      g_1->tete[k] = j;
      k++;
    }

  }

  return g_1;
}


graphe *
shortest_path( graphe * g,
	       int d,
	       int a)
{
  graphe * g_1;
  graphe * g_sym;
  long int* pi = g->v_sommets;
  pcell p;

  long int nsom, narc;
  nsom = g->nsom;
  narc = g->narc;
  g_1 = deep_copy(g);
  
  char * s = Dijkstra_eco(g, d, a);

  for (int i = 0; i < g->nsom; i++)
    if (s[i])
      g_1->v_sommets[i] = 1;
    else
      g_1->v_sommets[i] = 0;

  
  if (pi[a] == -1)
    return g_1;

  g_sym = Sym(g);
  

  long int x;
  long int y;

  x = a;
  
  while (x != d)
  {
    for (p = g_sym->gamma[x]; p != NULL; p = p->next) 
    {
      y = p->som;
      if (pi[x]-pi[y] == p->v_arc)
      {
	AjouteArcValue( g_1,
			y,
			x,
			p->v_arc );
	x = y;
	break;
      }
    }
    //    break;
  }
  TermineGraphe(g_sym);

  return g_1;
}

graphe *
smart_shortest_path( graphe * g,
		     int d,
		     int a,
		     int coeff)
{
  graphe * g_1;
  graphe * g_sym;
  long int* pi = g->v_sommets;
  pcell p;

  long int nsom, narc;
  nsom = g->nsom;
  narc = g->narc;
  g_1 = deep_copy(g);
  
  char * s = A_star(g, d, a, coeff);

  for (int i = 0; i < g->nsom; i++)
    if (s[i])
      g_1->v_sommets[i] = 1;
    else
      g_1->v_sommets[i] = 0;

  
  if (pi[a] == -1)
    return g_1;

  g_sym = Sym(g);
  

  long int x;
  long int y;

  x = a;
  
  while (x != d)
  {
    for (p = g_sym->gamma[x]; p != NULL; p = p->next) 
    {
      y = p->som;
      if (pi[x]-pi[y] == p->v_arc)
      {
	AjouteArcValue( g_1,
			y,
			x,
			p->v_arc );
	x = y;
	break;
      }
    }
    //    break;
  }
  TermineGraphe(g_sym);

  return g_1;
}


int
main( int argc,
      char **argv )
{
  // comme dans le 1.1.1
  graphe *g;
  char buf[256];
  
  if (argc != 2)
  {
    fprintf(stderr, "usage: %s <filename>\n%s\n", argv[0], USAGE);
    exit(0);
  }

  g = ReadGraphe(argv[1]);  /* lit le graphe a partir du fichier */

  
  ///////////

  
  Dijkstra(g, 0);

  for (int i = 0; i < g->nsom; i++)
    printf("%d :    %d \n", i, (g->v_sommets)[i]);
  
  //  graphe * short_g = shortest_path(g, 40, 60);
  graphe * short_g = smart_shortest_path(g, 40, 60, 4);
  printf("ENSEMBLE DES NOEUDS EXPLORES\n ");

  //  AfficheSuccesseurs(short_g);


  
  //PlongementCirculaire(g, 150);        /* plonge le graphe dans le plan */
  AutoNomsSommets(g, 1);               /* noms des sommet = indices */
  sprintf(buf, "tout_graphe.eps", argv[1]);     /* construit le nom du fichier PostScript */
  EPSGraphe(g, buf, 3, 0, 60, 0, 0, 0, 0);         /* genere une figure en PostScript */

  //PlongementCirculaire(short_g, 150);        /* plonge le graphe dans le plan */
  AutoNomsSommets(short_g, 1);
  sprintf(buf, "short_graphe.eps", argv[1]);
  EPSGraphe(short_g, buf, 3, 0, 60, 0, 0, 1, 0);
  
  ///////////
  TermineGraphe(g);
  TermineGraphe(short_g);
  return 0;

}
