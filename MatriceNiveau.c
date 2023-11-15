//
// Created by noeld on 14/11/2023.
//

#include "MatriceNiveau.h"
#include "Lecture_Fichier.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

struct File* creerFile(int taille) {
    struct File* q = malloc(sizeof(struct File));
    q->elements = malloc(taille * sizeof(int));
    q->tete = -1;
    q->queue = -1;
    q->taille = taille;
    return q;
}

bool FileVide(struct File* q) {
    return q->queue == -1;
}

int dequeue(struct File* q) {
    int element;
    if (FileVide(q)) {
        return -1;
    }
    element = q->elements[q->tete];
    q->tete++;
    if (q->tete > q->queue) {
        q->tete = q->queue = -1;
    }
    return element;
}

void FilePleine(struct File* q, int element) {
    if (q->queue == q->taille - 1) {
        return;
    }
    if (q->tete == -1) {
        q->tete = 0;
    }
    q->queue++;
    q->elements[q->queue] = element;
}

int* TrouverSommetsDepart(struct Graph* graph, int * nbSommetsDepart) {
    bool* estDestination = calloc(graph->nbSommet, sizeof(bool));
    for (int i = 0; i < graph->nbSommet; ++i) {
        struct Mat_adj* temp = graph->adjList[i];
        while (temp != NULL) {
            estDestination[temp->data] = true;
            temp = temp->next;
        }
    }

    // Compter et créer le tableau des sommets de départ
    for (int i = 0; i < graph->nbSommet; ++i) {
        // Un sommet est un sommet de départ s'il n'est pas une destination et a des successeurs
        if (!estDestination[i] && graph->adjList[i] != NULL) {
            (*nbSommetsDepart)++;
        }
    }
    int* sommetsDeparts = malloc(*nbSommetsDepart * sizeof(int));
    int index = 0;
    for (int i = 0; i < graph->nbSommet; ++i) {
        if (!estDestination[i] && graph->adjList[i] != NULL) {
            sommetsDeparts[index++] = i;
        }
    }
    free(estDestination);
    return sommetsDeparts;
}

// Fonction pour créer la matrice de niveaux
int** CreerMatriceNiveaux(struct Graph* graph, int * sommetsDepart, int nbSommetsDeparts) {
    int** matriceNiveaux = malloc(graph->nbSommet * sizeof(int*));

    for (int i = 0; i < graph->nbSommet; ++i) {
        matriceNiveaux[i] = malloc(graph->nbSommet * sizeof(int));
        for (int j = 0; j < graph->nbSommet; ++j) {
            matriceNiveaux[i][j] = -1;
        }
    }
    bool* visited = malloc(graph->nbSommet * sizeof(bool));
    for (int i = 0; i < graph->nbSommet; ++i) {
        visited[i] = false;
    }
    struct File* q = creerFile(graph->nbSommet);
    // Choisissez un sommet de départ, ici nous choisissons 0
    for (int i = 0; i < nbSommetsDeparts; ++i) {
        FilePleine(q, sommetsDepart[i]);
        visited[sommetsDepart[i]] = true;
    }
    int* predecesseurs = calloc(graph->nbSommet, sizeof(int));

// Parcourir toutes les arêtes pour compter les prédécesseurs
    for (int i = 0; i < graph->nbSommet; ++i) {
        struct Mat_adj* temp = graph->adjList[i];
        while (temp != NULL) {
            predecesseurs[temp->data]++;
            temp = temp->next;
        }
    }
    int niveau = 0;
    int matriceIndex = 0;
    while (!FileVide(q)) {
        int size = q->queue - q->tete + 1;
        for (int i = 0; i < size; ++i) {
            int sommet = dequeue(q);
            matriceNiveaux[niveau][matriceIndex++] = sommet;
            struct Mat_adj* temp = graph->adjList[sommet];
            while (temp) {
                int adjSommet = temp->data;
                predecesseurs[adjSommet]--;
                if (predecesseurs[adjSommet] == 0 && !visited[adjSommet]) {
                    visited[adjSommet] = true;
                    FilePleine(q, adjSommet);
                }
                temp = temp->next;
            }
        }
        niveau++;
        matriceIndex = 0;
    }
    free(visited);
    return matriceNiveaux;
}

void printMatriceNiveaux(int** matriceNiveaux, int nbSommet) {
    printf("Matrice des niveaux :\n");
    for (int i = 0; i < nbSommet; ++i) {
        printf("Niveau %d :", i);
        for (int j = 0; j < nbSommet; ++j) {
            if (matriceNiveaux[i][j] != -1) {
                printf(" %d", matriceNiveaux[i][j]);
            }
        }
        printf("\n");
    }
}