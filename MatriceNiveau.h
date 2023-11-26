//
// Created by noeld on 14/11/2023.
//

#ifndef PROJETTG_MATRICENIVEAU_H
#define PROJETTG_MATRICENIVEAU_H
#include "Lecture_Fichier.h"

typedef struct{
    int som;
    float poids;
}Sommet;

struct File {
    Sommet* elements;
    int tete;
    int queue;
    int taille;
};



struct File* creerFile(int taille);
Sommet dequeue(struct File* q);
void FilePleine(struct File* q, Sommet element);
Sommet* TrouverSommetsDepart(struct Graph* graph, int * nbSommetsDepart);
int* CreerMatriceNiveaux(struct Graph* graph, Sommet * sommetsDepart, int nbSommetsDeparts, Sommet*** matriceNiveaux);
void printMatriceNiveaux(Sommet ** matriceNiveaux, int nbSommet, int niveau);

#endif //PROJETTG_MATRICENIVEAU_H
