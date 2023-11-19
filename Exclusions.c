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



void descendreNiveauxSuivants(int** matriceNiveaux, int nbSommet, int niveauDebut, int sommetADescendre) {
    // Créer un espace au niveau suivant pour le sommet à descendre
    for (int i = nbSommet - 2; i >= niveauDebut; i--) {
        for (int j = 0; j < nbSommet; j++) {
            matriceNiveaux[i + 1][j] = matriceNiveaux[i][j];
        }
    }

    // Initialiser le niveau juste en dessous de niveauDebut
    for (int j = 0; j < nbSommet; j++) {
        matriceNiveaux[niveauDebut + 1][j] = -1;
    }

    // Déplacer le sommetADescendre au niveau suivant
    for (int j = 0; j < nbSommet; j++) {
        if (matriceNiveaux[niveauDebut][j] == sommetADescendre) {
            matriceNiveaux[niveauDebut][j] = -1;
            break;
        }
    }

    for (int j = 0; j < nbSommet; j++) {
        if (matriceNiveaux[niveauDebut + 1][j] == -1) {
            matriceNiveaux[niveauDebut + 1][j] = sommetADescendre;
            break;
        }
    }
}


void comparerExclusionsAvecMatriceNiveaux(int** matriceNiveaux, int nbSommet, t_exclusion* exclusions) {
    for (int i = 0; i < exclusions->nb_paires; i++) {
        int sommet1 = exclusions->paires[i].sommet1;
        int sommet2 = exclusions->paires[i].sommet2;
        int niveauSommet1 = -1, niveauSommet2 = -1;
        // Trouver les niveaux des deux sommets
        for (int j = 0; j < nbSommet; j++) {
            for (int k = 0; k < nbSommet; k++) {
                if (matriceNiveaux[j][k] == sommet1) niveauSommet1 = j;
                if (matriceNiveaux[j][k] == sommet2) niveauSommet2 = j;
            }
        }
        // Si les deux sommets sont au même niveau, descendre l'un d'eux
        if (niveauSommet1 != -1 && niveauSommet1 == niveauSommet2 && niveauSommet1 != nbSommet - 1)
        {
            if (sommet1>sommet2) {descendreNiveauxSuivants(matriceNiveaux, nbSommet, niveauSommet1, sommet1);}
            else descendreNiveauxSuivants(matriceNiveaux, nbSommet, niveauSommet1, sommet2);;
        }
    }
}