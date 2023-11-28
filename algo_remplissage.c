//
// Created by Gabriel Gasnier on 18/11/2023.
// Copyright (c) 2023 All rights reserved.
//

#include "algo_remplissage.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct{
    float duree;
    int* list_sommets;
    int nbSommets;
}graphe;

//mettre à jour les sommets disponibless
void mise_a_jour_liste_sommets_disponibles(int **matriceNiveaux, int* list_sommets,int nbSommets_total, int nbSommets_matrice, int nbNiveaux, int *sommetsDisponibles,
                                           int *nbSommetsDisponibles) {
    *nbSommetsDisponibles = 0;
    for (int i = 0; i < nbSommets_total; ++i) {
        int trouve = 0;
        for (int j = 0; j < nbNiveaux; ++j ) {
            for (int k = 0; k < nbSommets_matrice; ++k) {
                if (matriceNiveaux[j][k] == list_sommets[i]) {
                    trouve = 1;
                    break;
                }
            }
            }

        if (trouve == 0) {
            sommetsDisponibles[*nbSommetsDisponibles] = list_sommets[i];
            *nbSommetsDisponibles = *nbSommetsDisponibles + 1;
        }
    }
}

float initialisation_remplissage_niveau(int* niveau, int* list_operations,int taille_list_op ,float* duree_opreations){
    float duree_niveau = 0;
    int i;
    while (niveau[i] > 0){
        for (int j = 0; j < taille_list_op; ++j) {
            if (list_operations[j] == niveau[i]){
                duree_niveau = duree_niveau + duree_opreations[j];
            }
        }
    }
    return duree_niveau;
}




void descente_graphe(int* sommets_disponible,int nbSommets, int* niveau,int taille_niveau, int* list_sommets, int nbSommets_total,float* duree_operations, float duree_max_niveau){
    int niveau_actuel[35];
    float duree_niveau_actuel = initialisation_remplissage_niveau(niveau,list_sommets,nbSommets_total,duree_operations);

    graphe remplissage_actuel;
    for (int i = 0; i < nbSommets; ++i) {
        int sommet_actuel = sommets_disponible[i];
        for (int j = 0; j < list_sommets; ++j) {
            if ((list_sommets[j] == sommet_actuel) && (duree_max_niveau >= duree_niveau_actuel + duree_operations[sommet_actuel])){
                remplissage_actuel.list_sommets[remplissage_actuel.nbSommets] = list_sommets[j];
                remplissage_actuel.nbSommets = remplissage_actuel.nbSommets + 1;
                remplissage_actuel.duree = remplissage_actuel.duree + duree_operations[sommet_actuel];
            }
        }


    }


}



void remplissage_graphe(int** matriceNiveaux, int nbNiveaux, int nbSommets_matrice, int* list_sommets, int nbSommets_total, float* duree_operations, int* niveau, int taille_niveau){

    graphe meilleur_remplissage_actuel;
    graphe dernier_remplissage;
    meilleur_remplissage_actuel.list_sommets = malloc(nbSommets_total * sizeof(int));
    dernier_remplissage.list_sommets = malloc(nbSommets_total * sizeof(int));





}