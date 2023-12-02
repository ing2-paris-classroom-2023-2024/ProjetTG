//
// Created by vadzi on 12/11/2023.
//

#ifndef PROJETTG_LECTURE_FICHIER_H
#define PROJETTG_LECTURE_FICHIER_H

struct Mat_adj {
    int data;
    float poids;
    struct Mat_adj* next;
};

struct Graph {
    int nbSommet;
    struct Mat_adj** adjList;
};

struct Mat_adj* Creer_noeud(int value);
struct Graph* CreerGraph(int nbSommet);
void CreerArrete(struct Graph* graph, int src, int dest);
int est_un_sommet(struct Graph* graph, int i);
void printGraph(struct Graph* graph);
struct Graph* initGraph();
int nb_incompatibilites();
int* init_incompatibilites(int nbIncompatibilites);
void print_incompatibilites(int** incompatibilites, int nbIncompatibilites);
int nb_operations();
void init_operations(int nbOperations, int* num_operations, float* duree_operations);
float lire_cycle();
void print_operations(int nbOperations, int* num_operations, float* duree_operations);
#endif //PROJETTG_LECTURE_FICHIER_H
