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
    q->elements = malloc(taille * sizeof(Sommet));
    q->tete = -1;
    q->queue = -1;
    q->taille = taille;
    return q;
}


bool FileVide(struct File* q) {
    return q->queue == -1;
}

Sommet dequeue(struct File* q) {
    Sommet element;
    if (FileVide(q)) {
        element.som = -1;  // Ou une autre valeur par défaut
        element.poids = 0; // Ou une autre valeur par défaut
        return element;
    }
    element = q->elements[q->tete];
    q->tete++;
    if (q->tete > q->queue) {
        q->tete = q->queue = -1;
    }
    return element;
}

void FilePleine(struct File* q, Sommet element) {
    if (q->queue == q->taille - 1) {
        return;
    }
    if (q->tete == -1) {
        q->tete = 0;
    }
    q->queue++;
    q->elements[q->queue] = element;
}


Sommet* TrouverSommetsDepart(struct Graph* graph, int * nbSommetsDepart) {
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
    Sommet* sommetsDeparts = malloc(*nbSommetsDepart * sizeof(Sommet));
    int index = 0;
    for (int i = 0; i < graph->nbSommet; ++i) {
        if (!estDestination[i] && graph->adjList[i] != NULL) {
            sommetsDeparts[index++].som = i;
            sommetsDeparts[index].poids =0;
        }
    }
    free(estDestination);
    return sommetsDeparts;
}


int* CreerMatriceNiveaux(struct Graph* graph, Sommet * sommetsDepart, int nbSommetsDeparts, Sommet*** matriceNiveaux) {
    // Allouer de l'espace pour la matrice de structures Sommet
    (*matriceNiveaux) = malloc(graph->nbSommet * sizeof(Sommet *));
    for (int i = 0; i < graph->nbSommet; ++i) {
        (*matriceNiveaux)[i] = malloc(graph->nbSommet * sizeof(Sommet));
        for (int j = 0; j < graph->nbSommet; ++j) {
            // Initialisez les valeurs de la structure Sommet si nécessaire
            (*matriceNiveaux)[i][j].som = -1;
            (*matriceNiveaux)[i][j].poids = 0; // Par exemple, initialisez le poids à 0
        }
    }

    bool* visited = malloc(graph->nbSommet * sizeof(bool));
    for (int i = 0; i < graph->nbSommet; ++i) {
        visited[i] = false;
    }
    FILE* file;
    file = fopen("../operations.txt", "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier");
    }
    int src;
    float dest;
    while (fscanf(file, "%d %f", &src, &dest) == 2) {
        for (int i=0;i<nbSommetsDeparts;i++){
            if (src==sommetsDepart[i].som){
                sommetsDepart[i].poids=dest;
            }
        }
    }
    fclose(file);

    struct File* q = creerFile(graph->nbSommet);
    // Choisissez un sommet de départ, ici nous choisissons 0
    for (int i = 0; i < nbSommetsDeparts; i++) {
        Sommet sommet;
        sommet = sommetsDepart[i];; // Initialisation du poids à 0, vous pouvez le modifier si nécessaire
        FilePleine(q, sommet);
        visited[sommetsDepart[i].som] = true;
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
    int* niveau = malloc(sizeof(int));
    *niveau = 0;
    int matriceIndex = 0;
    while (!FileVide(q)) {
        int size = q->queue - q->tete + 1;
        for (int i = 0; i < size; i++) {
            Sommet sommet = dequeue(q);
            (*matriceNiveaux)[*niveau][matriceIndex] = sommet;
            matriceIndex++;

            struct Mat_adj* temp = graph->adjList[sommet.som];
            while (temp) {
                int adjSommet = temp->data;
                predecesseurs[adjSommet]--;
                if (predecesseurs[adjSommet] == 0 && !visited[adjSommet]) {
                    visited[adjSommet] = true;
                    Sommet adj;
                    adj.som = adjSommet;
                    adj.poids = temp->poids; // Récupérez le poids depuis la structure de graphe
                    FilePleine(q, adj);

                }
                temp = temp->next;
            }
        }
        (niveau)++;
        matriceIndex = 0;
    }
    free(visited);
    return niveau;
}






void printMatriceNiveaux(Sommet ** matriceNiveaux, int nbSommet, int niveau) {
    printf("Matrice des niveaux :\n");
    for (int i = 0; i < niveau; ++i) {
        printf("Niveau %d :", i);
        for (int j = 0; j < nbSommet; ++j) {
            if (matriceNiveaux[i][j].som != -1) {
                printf(" %d (%f)", matriceNiveaux[i][j].som, matriceNiveaux[i][j].poids );
            }

        } printf("\n");

    }

}
