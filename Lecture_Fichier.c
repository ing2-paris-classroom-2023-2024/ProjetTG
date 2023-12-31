//
// Created by vadzi on 12/11/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Lecture_Fichier.h"

struct Mat_adj* Creer_noeud(int value) {
    struct Mat_adj* noeud = (struct Mat_adj*)malloc(sizeof(struct Mat_adj));
    noeud->data = value;
    noeud->next = NULL;
    return noeud;
}

struct Graph* CreerGraph(int nbSommet) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->nbSommet = nbSommet;
    graph->adjList = (struct Mat_adj**)malloc(nbSommet * sizeof(struct Mat_adj*));
    for (int i = 0; i < nbSommet; ++i){
        graph->adjList[i] = NULL;
    }
    return graph;
}



void CreerArrete(struct Graph* graph, int src, int dest) {
    struct Mat_adj* noeud = Creer_noeud(dest);
    noeud->next = graph->adjList[src];
    graph->adjList[src] = noeud;
}

int est_un_sommet(struct Graph* graph, int i){
    return graph->adjList[i] != NULL;
}

void printGraph(struct Graph* graph) {
    for (int i = 0; i < graph->nbSommet; ++i) {
        if (!est_un_sommet(graph, i)) continue;
        struct Mat_adj* adj= graph->adjList[i];
        printf("Sommets adjacents a %d :", i);
        while (adj != NULL) {
            printf(" %d ", adj->data);
            adj = adj->next;
        }
        printf("\n");
    }
}

struct Graph* initGraph() {
    FILE *file;
    file = fopen("../precedences.txt", "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier");
    }
    int nbArrete = 0;
    int src, dest;
    while (fscanf(file, "%d %d", &src, &dest) == 2) {
        if (src > nbArrete) nbArrete = src;
        if (dest > nbArrete) nbArrete = dest;
    }
    fseek(file, 0, SEEK_SET);
    struct Graph *graph = CreerGraph(nbArrete + 1);
    while (fscanf(file, "%d %d", &src, &dest) == 2) {
        CreerArrete(graph, src, dest);
    }
    fclose(file);
    //printGraph(graph);
    return graph;
}

void print_incompatibilites(int** incompatibilites, int nbIncompatibilites){
    for (int i = 0; i < nbIncompatibilites; ++i) {
        printf("%d %d\n", incompatibilites[i][0], incompatibilites[i][1]);
    }
}

int nb_operations(){
    FILE *file;
    file = fopen("../operations.txt", "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier");
    }
    int nbOperations = 0;
    int src, dest;
    while (fscanf(file, "%d %f", &src, &dest) == 2) {
        nbOperations++;
    }
    fclose(file);
    return nbOperations;
}

void init_operations(int nbOperations, int* num_operations, float* duree_operations) {
    FILE* file;
    file = fopen("../operations.txt", "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier");
    }
    int src;
    float dest;
    int i = 0;
    while (fscanf(file, "%d %f", &src, &dest) == 2) {
        num_operations[i] = src;
        duree_operations[i] = dest;
        i++;
    }
    fclose(file);
}
void init_operationsDemo(int nbOperations, int* num_operations, float* duree_operations) {
    FILE* file;
    file = fopen("../operations.txt", "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier");
    }
    int src;
    float dest;
    int i = 0;
    while (fscanf(file, "%d %f", &src, &dest) == 2) {
        num_operations[src] = src;
        duree_operations[src] = dest;
        i++;
    }
    fclose(file);
}


float lire_cycle(){
    FILE* file;
    file = fopen("../cycle.txt", "r");
    float cycle = 0;
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier");
    }
    fscanf(file, "%f",&cycle);
    fclose(file);
    return cycle;
}

void print_operations(int nbOperations, int* num_operations, float* duree_operations){
    for (int i = 0; i < nbOperations; ++i) {
        printf("%d %.2f\n", num_operations[i], duree_operations[i]);
    }
}

