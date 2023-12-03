//
// Created by noeld on 14/11/2023.
//

#ifndef PROJETTG_MATRICENIVEAU_H
#define PROJETTG_MATRICENIVEAU_H
#include "Lecture_Fichier.h"
#include <stdbool.h>
typedef struct{
    int som;
    float poids;
}Sommet;

struct File {
    int* elements;
    int tete;
    int queue;
    int taille;
};



struct File* creerFile(int taille);
int dequeue(struct File* q);
void FilePleine(struct File* q, int element);
int* TrouverSommetsDepart(struct Graph* graph, int * nbSommetsDepart);
void initialiserVisited(bool* visited, int nbSommet);
void initialiserMatriceNiveaux(int*** matriceNiveaux, int nbSommet);
void ajouterSommetsDepartFile(struct File* q, bool* visited, int* SommetsDepart, int nbSommetsDeparts);
void compterPredecesseurs(struct Graph* graph, int* predecesseurs);
void traiterSommetsFile(struct File* q, bool* visited, int*** matriceNiveaux, int* predecesseurs, struct Graph* graph, int* niveau);
int* CreerMatriceNiveaux(struct Graph* graph, int nbSommetsDeparts, int*** matriceNiveaux, int* SommetsDepart);
void printMatriceNiveaux(int ** matriceNiveaux, int nbSommet, int niveau);

#endif //PROJETTG_MATRICENIVEAU_H
