//
// Created by Gabriel Gasnier on 18/11/2023.
// Copyright (c) 2023 All rights reserved.
//

#include "algo_remplissage.h"
#include "Exclusions.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

//obtenir la liste des sommets disponibles
int mise_a_jour_liste_sommets_disponibles(int **matriceNiveaux, int* list_sommets,int nbSommets_total, int nbNiveaux, int *sommetsDisponibles){
    int nbSommets = 0;
    int trouve[nbSommets_total];
    //marquer les sommets disponibles
    for (int i = 0; i < nbNiveaux; ++i) {
        int j = 0;
        while (matriceNiveaux[i][j] > 0){
            for (int k = 0; k < nbSommets_total; ++k) {
                trouve[k] = 0;
                if (matriceNiveaux[i][j] == list_sommets[k]) {
                    trouve[k] = 1;
                }
            }
            j++;
        }
    }
    //remplir la liste des sommets disponibles
    for (int i = 0; i < nbSommets_total; ++i) {
        if (trouve[i] == 0){
            sommetsDisponibles[nbSommets] = list_sommets[i];
            nbSommets++;
        }
    }

    return nbSommets;
}


void remplir_niveaux(int **matriceNiveaux, int *list_sommets, int nbSommets_total, float *liste_duree, int *nbNiveaux, float duree_max_niveau, t_exclusion *exclusions, int nbSommets_niveau_matrice) {
    //initialisation
    int *sommets_disponibles = malloc(nbSommets_total * sizeof(int));
    int nb_sommets_disponibles = mise_a_jour_liste_sommets_disponibles(matriceNiveaux, list_sommets, nbSommets_total, *nbNiveaux, sommets_disponibles);
    float *duree_niveaux_matrice = malloc(*nbNiveaux * sizeof(float));


    //calculer la duree de chaque niveau
    for (int i = 0; i < *nbNiveaux; ++i) {
        for (int j = 0; j < nbSommets_niveau_matrice; ++j) {
            duree_niveaux_matrice[i] += liste_duree[matriceNiveaux[i][j]];
        }
        printf("\nduree niveau %d : %f", i, duree_niveaux_matrice[i]);
    }

    //placer les sommets disponibles dans les niveaux
    for (int i = 0; i < nb_sommets_disponibles; i++) {
        int place = 0;
        for (int j = 0; j < *nbNiveaux; j++) {
            if (place == 0) {
                //verif de la duree valide
                if (duree_niveaux_matrice[j] + liste_duree[sommets_disponibles[i]] <= duree_max_niveau) {
                    int k = 0;
                    int incompatible = 0;
                    //verif des incompatibilites
                    while (matriceNiveaux[j][k] > 0) {
                        if (sont_incompatibles(matriceNiveaux[j][k], sommets_disponibles[i], exclusions) == 0) {
                            incompatible = 1;
                            break;
                        }
                        k++;
                    }
                    //placer le sommet
                    if (incompatible == 0) {
                        matriceNiveaux[j][k] = sommets_disponibles[i];
                        duree_niveaux_matrice[j] += liste_duree[sommets_disponibles[i]];
                        place = 1;
                        printf("\n%d a ete place dans le niveau %d", sommets_disponibles[i], j);
                        break;
                    }
                }
            }
        }

        //si le sommet n'a pas ete place, creer un nouveau niveau
        if (place == 0) {
            // créer un nouveau niveau
            (*nbNiveaux)++;
            int niveau = *nbNiveaux - 1;
            matriceNiveaux[niveau] = malloc(nbSommets_niveau_matrice * sizeof(int));
            for (int j = 0; j < nbSommets_niveau_matrice; j++) {
                matriceNiveaux[niveau][j] = -1;
            }
            matriceNiveaux[niveau][0] = sommets_disponibles[i];
            duree_niveaux_matrice = realloc(duree_niveaux_matrice, (*nbNiveaux) * sizeof(float));
            duree_niveaux_matrice[niveau] = liste_duree[sommets_disponibles[i]];

        }
    }

    free(sommets_disponibles);
    free(duree_niveaux_matrice);
}
