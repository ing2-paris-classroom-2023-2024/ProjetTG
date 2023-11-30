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
}graphe_r;

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

    float duree_niveau_actuel = initialisation_remplissage_niveau(niveau,list_sommets,nbSommets_total,duree_operations);

    graphe_r remplissage_actuel;
    for (int i = 0; i < nbSommets; ++i) {
        int sommet_actuel = sommets_disponible[i];
        for (int j = 0; j < list_sommets; ++j) {
            if ((list_sommets[j] == sommet_actuel) && (duree_max_niveau >= duree_niveau_actuel + duree_operations[sommet_actuel])){
                remplissage_actuel.list_sommets[remplissage_actuel.nbSommets] = list_sommets[j];
                remplissage_actuel.nbSommets = remplissage_actuel.nbSommets + 1;
                remplissage_actuel.duree = remplissage_actuel.duree + duree_operations[sommet_actuel];
                printf("sommet ajouté : %d", sommet_actuel);
                printf("duree actuelle : %f", remplissage_actuel.duree);
            }
            else{
                break;
            }
        }
    }
}



/*void remplissage_graphe(int** matriceNiveaux, int nbNiveaux, int nbSommets_matrice, int* list_sommets, int nbSommets_total, float* duree_operations, int* niveau, int taille_niveau){

    graphe_r meilleur_remplissage_actuel;
    graphe_r dernier_remplissage;
    meilleur_remplissage_actuel.list_sommets = malloc(nbSommets_total * sizeof(int));
    dernier_remplissage.list_sommets = malloc(nbSommets_total * sizeof(int));

}

void creer_graphe(struct Graph* graphe_r, int** matriceNiveaux, int nbNiveaux, int nbSommets_matrice, int nbSommets_total, float* duree_operations, t_exclusion* exclusions) {
    // Initialisation du graphe_r
    graphe_r->adjList = (struct Mat_adj**)malloc(nbSommets_total * sizeof(struct Mat_adj*));
    graphe_r->nbSommet = 0;
    struct Mat_adj* Sommet= (struct Mat_adj*)malloc(sizeof(struct Mat_adj));
    Sommet->data = matriceNiveaux[0][0];
    Sommet->poids = duree_operations[matriceNiveaux[0][0]];
    Sommet->next = NULL;

    // Ajouter le nouveau sommet à la liste d'adjacence
    graphe_r->adjList[graphe_r->nbSommet] = Sommet;
    graphe_r->nbSommet++;

    // Boucle sur les niveaux
    for (int i = 0; i < nbNiveaux; ++i) {
        // Boucle sur les sommets du niveau
        for (int j = 0; j < nbSommets_matrice; ++j) {
            int sommet = matriceNiveaux[i][j];

            // Vérifier l'incompatibilité avec les sommets déjà présents dans le graphe_r
            int compatible = 1;
            for (int k = 1; k < graphe_r->nbSommet; ++k) {
                printf("Comparaison %d et %d : %d\n", sommet, graphe_r->adjList[k-1]->data, sont_incompatibles(sommet, graphe_r->adjList[k]->data, exclusions));
                if (sont_incompatibles(sommet, graphe_r->adjList[k-1]->data, exclusions)) {
                    compatible = 0;
                    break;
                }
            }

            // Si le sommet est compatible, l'ajouter au graphe_r
            if (compatible) {
                struct Mat_adj* nvSommet = (struct Mat_adj*)malloc(sizeof(struct Mat_adj));
                nvSommet->data = sommet;
                nvSommet->poids = duree_operations[sommet];
                nvSommet->next = NULL;

                // Ajouter le nouveau sommet à la liste d'adjacence
                graphe_r->adjList[graphe_r->nbSommet] = nvSommet;
                graphe_r->nbSommet++;

                // Imprimer le sommet et sa durée
                printf("%d %f\n", sommet, duree_operations[sommet]);
            }
        }
    }
}*/