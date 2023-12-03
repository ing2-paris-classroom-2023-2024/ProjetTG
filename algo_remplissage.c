// Created by Gabriel Gasnier on 18/11/2023.
// Copyright (c) 2023 All rights reserved.
//

#include "algo_remplissage.h"
#include "Exclusions.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

int trouver_indice(int Atrouver, int *tab_sommets, int nbSommets){
    int indice = -1;
    for(int i =0; i<nbSommets; i++){
        if(Atrouver == tab_sommets[i]){
            return i;
        }
    }
    return indice;
}

int** remplissage_stations(int** matrice_niveau, float duree_max, int* taille_matrice, float *liste_duree, int* list_sommets, int nbSommets_total, t_exclusion* exclusions){
    int** nouvelle_matrice = malloc((*taille_matrice)*sizeof(int*));
    for (int i = 0; i < *taille_matrice; ++i) {
        nouvelle_matrice[i] = malloc((*taille_matrice)*sizeof(int));
        for (int j = 0; j < *taille_matrice; ++j) {
            nouvelle_matrice[i][j] = -1;
        }
    }

    int avancement_nouvelle_matrice_ligne = 0;
    int avancement_nouvelle_matrice_colonne[*taille_matrice];
    for(int i =0; i<(*taille_matrice); i++){
        avancement_nouvelle_matrice_colonne[i]= 0;
    }
    for (int i = 0; i < *taille_matrice; ++i) {
        int k = 0;
        int incompatibilite_ligne = 0;
        while (matrice_niveau[i][k] != -1){
            int l = 0;
            int incompatible = 0;
            float duree = 0;
            while (nouvelle_matrice[avancement_nouvelle_matrice_ligne][l] != -1){
                if (sont_incompatibles(nouvelle_matrice[avancement_nouvelle_matrice_ligne][l], matrice_niveau[i][k], exclusions) == 1){
                    incompatible = 1;
                    break;
                }
                duree += liste_duree[trouver_indice(nouvelle_matrice[avancement_nouvelle_matrice_ligne][l], list_sommets, nbSommets_total)];
                l++;
            }

            if (incompatible == 0 && duree + liste_duree[trouver_indice(matrice_niveau[i][k], list_sommets, nbSommets_total)] <= duree_max){
                nouvelle_matrice[avancement_nouvelle_matrice_ligne][avancement_nouvelle_matrice_colonne[avancement_nouvelle_matrice_ligne]] = matrice_niveau[i][k];
                avancement_nouvelle_matrice_colonne[avancement_nouvelle_matrice_ligne]++;
            }
            else {
                nouvelle_matrice[avancement_nouvelle_matrice_ligne+1][avancement_nouvelle_matrice_colonne[avancement_nouvelle_matrice_ligne+1]] = matrice_niveau[i][k];
                avancement_nouvelle_matrice_colonne[avancement_nouvelle_matrice_ligne+1]++;
                incompatibilite_ligne = 1;
            }
            k++;
        }
        if (incompatibilite_ligne == 1){
            avancement_nouvelle_matrice_ligne++;

        }

    }
    *taille_matrice = avancement_nouvelle_matrice_ligne + 1;
    return nouvelle_matrice;
}