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
float initialisation_remplissage_niveau(int* niveau, int* list_operations,int taille_list_op ,float* duree_opreations);
void descente_graphe(int* sommets_disponible,int nbSommets, int* niveau,int taille_niveau, int* list_sommets, int nbSommets_total,float* duree_operations, float duree_max_niveau);

//void creer_graphe(struct Graph* graphe, int** matriceNiveaux, int nbNiveaux, int nbSommets_matrice, int nbSommets_total, float* duree_operations, t_exclusion* exclusions);
#endif //PROJETTG_ALGO_REMPLISSAGE_H
