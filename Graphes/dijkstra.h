#include <stdlib.h>
#include <stdio.h>
#include "graphaux.h"
#include "graphes.h"




graphe * Sym(graphe * g);

void Dijkstra(graphe * g, int i);

char  *
Dijkstra_eco(graphe * g, int i, int but);

double // retourne la distance entre i et j dans g
heuristic_dist(graphe * g, int i, int j);

long // retourne le poid du noeud x avec critère géographique
heuristic(graphe * g, int x, int but, int coeff);

char * // notre Dijkstra_eco modifié pour en faire un A*
A_star(graphe * g, int i, int but, int coeff);

graphe * // clone un graphe
deep_copy(graphe * g);

graphe *
shortest_path( graphe * g,
	       int d,
	       int a);

graphe *
smart_shortest_path( graphe * g,
		     int d,
		     int a,
		     int coeff);

char *
A_star_quick(graphe * g, int i, int but, int coeff);


graphe *
smarter_shortest_path( graphe * g,
		       int d,
		       int a,
		       int coeff);
