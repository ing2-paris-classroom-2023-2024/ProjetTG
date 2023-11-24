#include <stdio.h>
#include <stdlib.h>
#include "Lecture_Fichier.h"
#include "MatriceNiveau.h"
#include "Exclusions.h"
#include "algo_remplissage.h"

int main(){
    int nbOperations = nb_operations();
    int* num_operations = malloc(nbOperations * sizeof(int));
    float* duree_operations = malloc(nbOperations * sizeof(float));
    init_operations(nbOperations, num_operations, duree_operations);
    struct Graph* graphe = initGraph();
    int nb_sommets_depart=0;
    int * sommetsDepart = TrouverSommetsDepart(graphe, &nb_sommets_depart);
    int** matriceNiveaux = malloc(graphe->nbSommet * sizeof(int*));
    t_sommets sommets;
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
    printMatriceNiveaux(matriceNiveaux, graphe->nbSommet, *niveau);/*
   printf("affichage des sommets");
    sommets = MAJ_sommets(matriceNiveaux,graphe->nbSommet,*niveau,num_operations,duree_operations,nbOperations);
    print_Maj_sommet(*niveau,graphe->nbSommet,sommets);*/
    //printf("\n%d",sont_incompatibles(1, 4, exclusions));

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