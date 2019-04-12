#include "dijkstra.h"
#include "tas_binaire.h"
#define USAGE "tests <filel>"



void
test_dijkstra(graphe* g, char * buf, char **argv, int start, int goal)
{
  Dijkstra(g, start);

  for (int i = 0; i < g->nsom; i++)
    printf("%d :    %d \n", i, (g->v_sommets)[i]);
  graphe * short_g = shortest_path(g, start, goal);

  sprintf(buf, "dijkstra.eps", argv[1]);
  EPSGraphe(short_g, buf, 3, 0, 60, 0, 0, 1, 0);

  TermineGraphe(short_g);
}

void
test_a_star(graphe* g, char * buf, char **argv, int start, int goal, int coeff)
{
  graphe * short_g = smart_shortest_path(g, start, goal, coeff);

  sprintf(buf, "a_star.eps", argv[1]);
  EPSGraphe(short_g, buf, 3, 0, 60, 0, 0, 1, 0); 
  TermineGraphe(short_g);
}


void
test_tas(graphe * g, int start)
{
    Dijkstra(g, start);


  tas_binaire tas = cree_tas();
  printf("\n");
  affiche_tas(tas);
  printf("\n");

  for (int i = 0; i < g->nsom; i++)
  {

    printf("g[%d] %d \n", i, g->v_sommets[i]);
    ajoute_sommet(&tas, g, i);
    affiche_tas(tas);
  }
  
  printf("\nPAR POIDS:\n");
  affiche_tas_poids(tas, g);
  printf("\n");

  int i = minimum_tas(tas);
  printf("minimum_tas: g[%d] = %d \n", i, g->v_sommets[i]);

  while (tas)
  {
    i = pop_max(&tas);
    printf("%d %d\n", i, g->v_sommets[i]);
  }
  printf("\n");    
  libere_tas(tas);

}

int
main( int argc,
      char **argv )
{
  // comme dans le 1.1.1
  graphe *g;
  char buf[256];
  int start;
  int goal;
  int coeff;
  printf("start end coeff: ");
  scanf("%d %d %d", &start, &goal, &coeff);
  
  if (argc != 2)
  {
    fprintf(stderr, "usage: %s <filename>\n%s\n", argv[0], USAGE);
    exit(0);
  }


  g = ReadGraphe(argv[1]);  /* lit le graphe a partir du fichier */

  
  ///////////

  test_dijkstra(g, buf, argv, start, goal);
  test_a_star(g, buf, argv, start, goal, coeff);
  //  test_tas(g, start);

  ///////////
  TermineGraphe(g);
  return 0;

}
