//
// Created by noeld on 19/11/2023.
//

#include "Exclusions.h"
#include "Lecture_Fichier.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


t_exclusion* lireExclusions() {
    FILE* fichier = fopen("../exclusions.txt", "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier d'exclusions");
        return NULL;
    }

    t_exclusion* exclusions = malloc(sizeof(t_exclusion));
    exclusions->paires = malloc(100 * sizeof(t_paireExclusion));  // Taille initiale
    exclusions->nb_paires = 0;
    int capacite = 100;

    int src, dest;
    while (fscanf(fichier, "%d %d", &src, &dest) == 2) {
        if (exclusions->nb_paires >= capacite) {
            capacite *= 2;
            exclusions->paires = realloc(exclusions->paires, capacite * sizeof(t_paireExclusion));
        }
        exclusions->paires[exclusions->nb_paires].sommet1 = src;
        exclusions->paires[exclusions->nb_paires].sommet2 = dest;
        exclusions->nb_paires++;
    }

    fclose(fichier);
    return exclusions;
}

void afficherPaires(t_exclusion* exclusions) {
    if (exclusions == NULL) {
        printf("Pas d'exclusions à afficher.\n");
        return;
    }

    for (int i = 0; i < exclusions->nb_paires; i++) {
        printf("Paire %d : Sommet1 = %d, Sommet2 = %d\n",
               i+1,
               exclusions->paires[i].sommet1,
               exclusions->paires[i].sommet2);
    }
}

bool dfs(struct Graph* graph, int start, int end, bool visited[]) {
    if (start == end) return true;

    visited[start] = true;
    struct Mat_adj* temp = graph->adjList[start];
    while (temp != NULL) {
        int adjVertex = temp->data;
        if (!visited[adjVertex]) {
            if (dfs(graph, adjVertex, end, visited)) return true;
        }
        temp = temp->next;
    }
    return false;
}

bool estPrecedent(struct Graph* graph, int sommet1, int sommet2) {
    bool* visited = (bool*)malloc(graph->nbSommet * sizeof(bool));
    for (int i = 0; i < graph->nbSommet; ++i) {
        visited[i] = false;
    }

    bool result = dfs(graph, sommet1, sommet2, visited);
    free(visited);
    return result;
}

bool estPrecedentALigne(struct Graph* graph, int sommet, int** matriceNiveaux, int ligneIndex, int nbSommets) {
    for (int i = 0; i < nbSommets; ++i) {
        int sommetLigne = matriceNiveaux[ligneIndex][i];
        if (sommetLigne != -1 && estPrecedent(graph, sommet, sommetLigne)) {
            return true; // `sommet` est précédent à au moins un sommet dans la ligne
        }
    }
    return false; // `sommet` n'est précédent à aucun sommet dans la ligne
}



void descendreNiveauxSuivants(struct Graph* g,int*** matriceNiveaux, int* niveau, int nbSommet, int niveauDebut, int sommetADescendre) {
    // Vérifier et augmenter la taille de la matrice si nécessaire
    if(estPrecedentALigne(g, sommetADescendre, *matriceNiveaux, niveauDebut+1, nbSommet)){
        *niveau += 1;
        *matriceNiveaux = realloc(*matriceNiveaux, (*niveau) * sizeof(int*));
        (*matriceNiveaux)[*niveau - 1] = malloc(nbSommet * sizeof(int));
        for (int j = 0; j < nbSommet; j++) {
            (*matriceNiveaux)[*niveau - 1][j] = -1;
        }
        // Décaler les niveaux
        for (int i = *niveau - 2; i > niveauDebut; i--) {
            for (int j = 0; j < nbSommet; j++) {
                (*matriceNiveaux)[i + 1][j] = (*matriceNiveaux)[i][j];
            }
        }
        // Initialiser le niveau juste en dessous de niveauDebut
        for (int j = 0; j < nbSommet; j++) {
            (*matriceNiveaux)[niveauDebut + 1][j] = -1;
        }
    }
    // Déplacer le sommet au niveau suivant
    for (int j = 0; j < nbSommet; j++) {
        if ((*matriceNiveaux)[niveauDebut][j] == sommetADescendre) {
            (*matriceNiveaux)[niveauDebut][j] = -1;
            break;
        }
    }

    // Ajouter le sommet au niveau suivant
    for (int j = 0; j < nbSommet; j++) {
        if ((*matriceNiveaux)[niveauDebut + 1][j] == -1) {
            (*matriceNiveaux)[niveauDebut + 1][j] = sommetADescendre;
            break;
        }
    }
}



void comparerExclusionsAvecMatriceNiveaux(struct Graph* g, int*** matriceNiveaux, int* niveau, int nbSommet, t_exclusion* exclusions) {
    for (int i = 0; i < exclusions->nb_paires; i++) {
        int sommet1 = exclusions->paires[i].sommet1;
        int sommet2 = exclusions->paires[i].sommet2;
        int niveauSommet1 = -1, niveauSommet2 = -1;

        // Trouver les niveaux des deux sommets
        for (int j = 0; j < *niveau; j++) {
            for (int k = 0; k < nbSommet; k++) {
                if ((*matriceNiveaux)[j][k] == sommet1) niveauSommet1 = j;
                if ((*matriceNiveaux)[j][k] == sommet2) niveauSommet2 = j;
            }
        }

        // Si les deux sommets sont au même niveau, descendre l'un d'eux
        if (niveauSommet1 != -1 && niveauSommet1 == niveauSommet2) {
            if (sommet1 > sommet2) {
                descendreNiveauxSuivants(g, matriceNiveaux, niveau, nbSommet, niveauSommet1, sommet1);
            } else {
                descendreNiveauxSuivants(g, matriceNiveaux, niveau, nbSommet, niveauSommet1, sommet2);
            }
        }
    }
}



int sont_incompatibles(int sommet1, int sommet2, t_exclusion* exclusions) {
    for (int i = 0; i < exclusions->nb_paires; i++) {
        if ((exclusions->paires[i].sommet1 == sommet1 && exclusions->paires[i].sommet2 == sommet2) ||
            (exclusions->paires[i].sommet1 == sommet2 && exclusions->paires[i].sommet2 == sommet1)) {
            return 1;
        }
    }
    return 0;
}