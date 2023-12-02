//
// Created by Gabriel Gasnier on 18/11/2023.
// Copyright (c) 2023 All rights reserved.
//

#ifndef PROJETTG_ALGO_REMPLISSAGE_H
#define PROJETTG_ALGO_REMPLISSAGE_H
#include "Lecture_Fichier.h"
#include "MatriceNiveau.h"
#include "Exclusions.h"


int mise_a_jour_liste_sommets_disponibles(int **matriceNiveaux, int* list_sommets,int nbSommets_total, int nbNiveaux, int *sommetsDisponibles);
void remplir_niveaux(int **matriceNiveaux, int* list_sommets, int nbSommets_total, float* liste_duree, int* nbNiveaux, float duree_max_niveau, t_exclusion* exclusions, int nbSommets_nivau_matrice);

//void creer_graphe(struct Graph* graphe, int** matriceNiveaux, int nbNiveaux, int nbSommets_matrice, int nbSommets_total, float* duree_operations, t_exclusion* exclusions);
#endif //PROJETTG_ALGO_REMPLISSAGE_H
