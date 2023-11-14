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
        printf("Sommets adjacents à %d :", i);
        while (adj != NULL) {
            printf(" %d", adj->data);
            adj = adj->next;
        }
        printf("\n");
    }
}

struct Graph* lecture_fichier() {
    FILE *file;
    file = fopen("precedences.txt", "r");
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
    struct Graph* graph = CreerGraph(nbArrete + 1);
    while (fscanf(file, "%d %d", &src, &dest) == 2) {
        CreerArrete(graph, src, dest);
    }
    fclose(file);
    printGraph(graph);
    return graph;
}