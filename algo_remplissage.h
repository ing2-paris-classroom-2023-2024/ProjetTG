//
// Created by Gabriel Gasnier on 18/11/2023.
// Copyright (c) 2023 All rights reserved.
//

#ifndef PROJETTG_ALGO_REMPLISSAGE_H
#define PROJETTG_ALGO_REMPLISSAGE_H
typedef struct {
    int* sommets;
    float* taille;
} t_sommets;

typedef struct f_File {
    t_sommets * elements;
    int tete;
    int queue;
    int taille;
} t_File;
t_sommets MAJ_sommets(int** matriceNiveaux, int nbSommet, int niveau,int* num_operations, float* duree_operations, int nbOperations);
void print_Maj_sommet(int niveau,int nbSommet,t_sommets sommets);

#endif //PROJETTG_ALGO_REMPLISSAGE_H
