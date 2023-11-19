#include <stdio.h>
#include <stdlib.h>
#include "Lecture_Fichier.h"
#include "MatriceNiveau.h"
#include "Exclusions.h"

int main(){

   struct Graph* graphe = initGraph();
    int nb_sommets_depart=0;
    int * sommetsDepart = TrouverSommetsDepart(graphe, &nb_sommets_depart);
    for(int i=0; i<nb_sommets_depart; i++){
        printf("%d\n", sommetsDepart[i]);
    }
    int** matriceNiveaux = malloc(graphe->nbSommet * sizeof(int*));
    int niveau = CreerMatriceNiveaux(graphe, sommetsDepart, nb_sommets_depart, matriceNiveaux);
    printf("\nMatrice des niveaux :\n\n");
    printMatriceNiveaux(matriceNiveaux, graphe->nbSommet, niveau);

    /*int NbIncompatibilites = nb_incompatibilites();
    int* incompatibilites = init_incompatibilites(NbIncompatibilites);
    printf("\nIncompatibilites :\n\n");
    print_incompatibilites(incompatibilites, NbIncompatibilites);*/
    t_exclusion * exclusions = lireExclusions();
    afficherPaires(exclusions);
    comparerExclusionsAvecMatriceNiveaux(matriceNiveaux,graphe->nbSommet, exclusions);
    printf("\nMatrice des niveaux avec exclusions :\n\n");
    printMatriceNiveaux(matriceNiveaux, graphe->nbSommet, niveau);


    int nbOperations = nb_operations();
    int* num_operations = malloc(nbOperations * sizeof(int));
    float* duree_operations = malloc(nbOperations * sizeof(float));
    init_operations(nbOperations, num_operations, duree_operations);
    printf("\n\nOperations :\n\n");
    print_operations(nbOperations, num_operations, duree_operations);

    //free(incompatibilites);
    free(num_operations);
    free(duree_operations);
    free(sommetsDepart);
    free(graphe);
    free(matriceNiveaux);
    return 0;

}
