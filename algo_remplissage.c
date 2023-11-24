//
// Created by Gabriel Gasnier on 18/11/2023.
// Copyright (c) 2023 All rights reserved.
//

#include "algo_remplissage.h"
#include "Lecture_Fichier.h"
#include "MatriceNiveau.h"
#include "Exclusions.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct f_File {
    int* elements;
    int tete;
    int queue;
    int taille;
} t_File;

typedef struct {
    int* sommets;
    float taille;
} t_sommets;

// déscente de graphe


void MAJ_sommets(int** matriceNiveaux, int nbSommet, int niveau,t_sommets sommets) {
    int nbOperations = nb_operations();
    int* num_operations = malloc(nbOperations * sizeof(int));
    float* duree_operations = malloc(nbOperations * sizeof(float));
    init_operations(nbOperations, num_operations, duree_operations);
    for (int i = 0; i < niveau; ++i) {
        for (int j = 0; j < nbSommet; ++j) {
            if (matriceNiveaux[i][j] != -1) {
                for (int k = 0; k < nbOperations; ++k) {
                    if (matriceNiveaux[i][j] == num_operations[k]) {
                        sommets.sommets[j] =matriceNiveaux[i][j];
                        sommets.taille = duree_operations[k];
                    }
                }
            }
        }
    }
}

