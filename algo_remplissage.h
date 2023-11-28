//
// Created by Gabriel Gasnier on 18/11/2023.
// Copyright (c) 2023 All rights reserved.
//

#ifndef PROJETTG_ALGO_REMPLISSAGE_H
#define PROJETTG_ALGO_REMPLISSAGE_H
#include "Lecture_Fichier.h"
#include "MatriceNiveau.h"
#include "Exclusions.h"


void mise_a_jour_liste_sommets_disponibles(int **matriceNiveaux, int* list_sommets,int nbSommets_total, int nbSommets_matrice, int nbNiveaux, int *sommetsDisponibles,
                                           int *nbSommetsDisponibles);


#endif //PROJETTG_ALGO_REMPLISSAGE_H
