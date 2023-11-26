//
// Created by noeld on 19/11/2023.
//

#ifndef PROJETTG_EXCLUSIONS_H
#define PROJETTG_EXCLUSIONS_H
#include "Lecture_Fichier.h"
#include "MatriceNiveau.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int sommet1;
    int sommet2;
} t_paireExclusion;

typedef struct {
    t_paireExclusion* paires;
    int nb_paires;
} t_exclusion;


t_exclusion* lireExclusions();
void descendreNiveauxSuivants(struct Graph* g, Sommet**** matriceNiveaux, int* niveau, int nbSommet, int niveauDebut, int sommetADescendre);
void comparerExclusionsAvecMatriceNiveaux(struct Graph* g, Sommet*** matriceNiveaux, int* niveau, int nbSommet, t_exclusion* exclusions);
bool estPrecedentALigne(struct Graph* graph, int sommet, Sommet** matriceNiveaux, int ligneIndex, int nbSommets);
bool estPrecedent(struct Graph* graph, int sommet1, int sommet2) ;
bool dfs(struct Graph* graph, int start, int end, bool visited[]);

void afficherPaires(t_exclusion* exclusions);
int sont_incompatibles(int sommet1, int sommet2, t_exclusion* exclusions);

#endif //PROJETTG_EXCLUSIONS_H
