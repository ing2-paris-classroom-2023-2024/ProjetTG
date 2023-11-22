//
// Created by noeld on 19/11/2023.
//

#include "Exclusions.h"
#include <stdlib.h>
#include <stdio.h>


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

void descendreNiveauxSuivants(int*** matriceNiveaux, int* niveau, int nbSommet, int niveauInMat, int sommetADescendre) {
    // Vérifier et augmenter la taille de la matrice si nécessaire
    *niveau += 1;
    *matriceNiveaux = realloc(*matriceNiveaux, (*niveau) * sizeof(int*));
    (*matriceNiveaux)[*niveau - 1] = malloc(nbSommet * sizeof(int));
    for (int j = 0; j < nbSommet; j++) {
        (*matriceNiveaux)[*niveau - 1][j] = -1;
    }
    // Décaler les niveaux
    for (int i = *niveau - 2; i > niveauInMat; i--) {
        for (int j = 0; j < nbSommet; j++) {
            (*matriceNiveaux)[i + 1][j] = (*matriceNiveaux)[i][j];
        }
    }

    // Initialiser le niveau juste en dessous de niveauInMat
    for (int j = 0; j < nbSommet; j++) {
        (*matriceNiveaux)[niveauInMat + 1][j] = -1;
    }

    // Déplacer le sommet au niveau suivant
    for (int j = 0; j < nbSommet; j++) {
        if ((*matriceNiveaux)[niveauInMat][j] == sommetADescendre) {
            (*matriceNiveaux)[niveauInMat][j] = -1;
            break;
        }
    }

    // Ajouter le sommet au niveau suivant
    for (int j = 0; j < nbSommet; j++) {
        if ((*matriceNiveaux)[niveauInMat + 1][j] == -1) {
            (*matriceNiveaux)[niveauInMat + 1][j] = sommetADescendre;
            break;
        }
    }
}



void comparerExclusionsAvecMatriceNiveaux(int*** matriceNiveaux, int* niveau, int nbSommet, t_exclusion* exclusions) {
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
                descendreNiveauxSuivants(matriceNiveaux, niveau, nbSommet, niveauSommet1, sommet1);
            } else {
                descendreNiveauxSuivants(matriceNiveaux, niveau, nbSommet, niveauSommet1, sommet2);
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