#include <stdio.h>
#include <stdlib.h>
#include "Lecture_Fichier.h"
#include "MatriceNiveau.h"
#include "Exclusions.h"

int main(){

    struct Graph* graphe = initGraph();
    int nb_sommets_depart=0;
    int * sommetsDepart = TrouverSommetsDepart(graphe, &nb_sommets_depart);
    int** matriceNiveaux = malloc(graphe->nbSommet * sizeof(int*));

    int* niveau = CreerMatriceNiveaux(graphe, sommetsDepart, nb_sommets_depart, matriceNiveaux);
    printf("\nMatrice des niveaux :\n\n");
    printMatriceNiveaux(matriceNiveaux, graphe->nbSommet, *niveau);
    for(int k=0;k<graphe->nbSommet;k++){
        estPrecedentALigne(graphe, 6,matriceNiveaux,1,graphe->nbSommet);
    }
    t_exclusion * exclusions = lireExclusions();
    //afficherPaires(exclusions);
    comparerExclusionsAvecMatriceNiveaux(graphe, &matriceNiveaux,niveau, graphe->nbSommet, exclusions);
    printf("\nMatrice des niveaux avec exclusions :\n\n");
    printMatriceNiveaux(matriceNiveaux, graphe->nbSommet, *niveau);
    //printf("%d",sont_incompatibles(1, 4, exclusions));
    int nbOperations = nb_operations();
    int* num_operations = malloc(nbOperations * sizeof(int));
    float* duree_operations = malloc(nbOperations * sizeof(float));
    init_operations(nbOperations, num_operations, duree_operations);
    printf("\n\nOperations :\n\n");
    //print_operations(nbOperations, num_operations, duree_operations);

    //free(incompatibilites);
    free(num_operations);
    free(duree_operations);
    free(sommetsDepart);
    free(graphe);
    free(matriceNiveaux);
    return 0;
}