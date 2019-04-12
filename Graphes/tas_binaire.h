typedef struct _noeud_tas_binaire
{
  int sommet;
  struct _noeud_tas_binaire * gauche;
  struct _noeud_tas_binaire * droite;
} noeud_tas_binaire, *tas_binaire;



tas_binaire
cree_tas(void);

int
tas_est_vide(tas_binaire tas);

void
ajoute_sommet(tas_binaire *tas, graphe * g, int i);

void
affiche_tas(tas_binaire tas);

void
affiche_tas_poids(tas_binaire tas, graphe * g);

void
libere_tas(tas_binaire tas);

int
minimum_tas(tas_binaire tas);

int
maximum_tas(tas_binaire tas);

int
pop_max(tas_binaire *tas);

int
pop_min(tas_binaire *tas);

int
pop_tas(tas_binaire *tas);
