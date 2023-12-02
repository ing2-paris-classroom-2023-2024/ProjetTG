//
// Created by Gabriel Gasnier on 18/11/2023.
// Copyright (c) 2023 All rights reserved.
//

#ifndef PROJETTG_ALGO_REMPLISSAGE_H
#define PROJETTG_ALGO_REMPLISSAGE_H
#include "Lecture_Fichier.h"
#include "MatriceNiveau.h"
#include "Exclusions.h"


int trouver_indice(int Atrouver, int *tab_sommets, int nbSommets);
int** remplissage_stations(int** matrice_niveau, float duree_max, int* taille_matrice, float *liste_duree, int* list_sommets, int nbSommets_total, t_exclusion* exclusions);

#endif //PROJETTG_ALGO_REMPLISSAGE_H
