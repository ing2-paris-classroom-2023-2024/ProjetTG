#include <stdio.h>
#include "Lecture_Fichier.h"
#include "MatriceNiveau.h"

int main() {
    struct Graph* graphe = initGraph();
    int nb_sommets_depart=0;
    int * sommetsDepart = TrouverSommetsDepart(graphe, &nb_sommets_depart);
    for(int i=0; i<nb_sommets_depart; i++){
        printf("%d\n", sommetsDepart[i]);
    }
    int** matriceNiveaux = CreerMatriceNiveaux(graphe, sommetsDepart, nb_sommets_depart);
    printMatriceNiveaux(matriceNiveaux, graphe->nbSommet);

}
