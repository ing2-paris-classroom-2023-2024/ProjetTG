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




// déscente de graphe


t_sommets MAJ_sommets(int** matriceNiveaux, int nbSommet, int niveau,int* num_operations, float* duree_operations, int nbOperations) {
    t_sommets sommets;
    t_File sommet;
    for (int i = 0; i < niveau; ++i) {
        for (int j = 0; j < nbSommet; ++j) {
            if (matriceNiveaux[i][j] != -1) {
                for (int k = 0; k < nbOperations; ++k) {
                    if (matriceNiveaux[i][j] == num_operations[k]) {
                        sommets.sommets[j] =matriceNiveaux[i][j];
                        sommets.taille[j] = duree_operations[k];
                        //sommet.elements = &sommets;
                    }
                }
            }
        }
    }
    return sommets;
}

void print_Maj_sommet(int niveau,int nbSommet,t_sommets sommets){
    for (int i=0; i<niveau;i++){
        for (int j=0; j< nbSommet;j++ ){
            printf("\n%d %f", sommets.sommets[j], sommets.taille[j]);
        }
    }
}