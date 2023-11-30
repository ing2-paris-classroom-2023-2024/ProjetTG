#include <stdio.h>
#include <stdlib.h>
#include "Lecture_Fichier.h"
#include "MatriceNiveau.h"
#include "Exclusions.h"
#include "algo_remplissage.h"

//remplir une liste de tous les sommets de la matrice
void remplir_liste_sommets(int** MatriceNiveaux, int* liste_sommet, int nb_sommet, int niveau){
    int k = 0;
    for (int i = 0; i < niveau; ++i) {
        for (int j = 0; j < nb_sommet; ++j) {

            if ((MatriceNiveaux[i][j] != -1)&& (MatriceNiveaux[i][j] != 0)){
                liste_sommet[k] = MatriceNiveaux[i][j];
                printf("%d ", liste_sommet[k]);
                k++;
            }
        }
    }
}
int main(){
    int nbOperations = nb_operations();
    int* num_operations = malloc(nbOperations * sizeof(int));
    float* duree_operations = malloc(nbOperations * sizeof(float));
    struct Graph* graphe = initGraph();
    int nb_sommets_depart=0;
    int * sommetsDepart = TrouverSommetsDepart(graphe, &nb_sommets_depart);
    //printf("\n\nOperations :\n\n");
    init_operations(nbOperations, num_operations, duree_operations, graphe);
    //printGraph(graphe);
    //print_operations(nbOperations, num_operations, duree_operations);
    int **matriceNiveaux;
    int *niveau = CreerMatriceNiveaux(graphe,  nb_sommets_depart, &matriceNiveaux,sommetsDepart);
    //t_sommets sommets;
    printf("\nMatrice des niveaux :\n\n");
    //printMatriceNiveaux(matriceNiveaux, graphe->nbSommet, *niveau);
    t_exclusion * exclusions = lireExclusions();
    //afficherPaires(exclusions);
    comparerExclusionsAvecMatriceNiveaux(graphe, &matriceNiveaux,niveau, graphe->nbSommet, exclusions);
    printf("\nMatrice des niveaux avec exclusions :\n\n");
    //printMatriceNiveaux(matriceNiveaux, graphe->nbSommet, *niveau);

    int *list_sommets = malloc(graphe->nbSommet * sizeof(int));
    printf("\nListe des sommets :\n\n");
    //rempli le liste sommet a partir du graphe directement (pas de doublons)
    remplir_liste_sommets(matriceNiveaux, list_sommets, graphe->nbSommet, *niveau);
    int nb_sommets = 0;
    for (int i = 0; i < graphe->nbSommet; ++i) {
        if (list_sommets[i] != 0){
            nb_sommets++;
        }
    }
    for (int i = 0; i < nb_sommets; ++i) {
        printf("\n%d ", list_sommets[i]);
    }


    int nbSommetsDisponibles = 0;
    int *sommetsDisponibles = malloc(graphe->nbSommet * sizeof(int));
    mise_a_jour_liste_sommets_disponibles(matriceNiveaux, list_sommets, nb_sommets, nb_sommets, *niveau, sommetsDisponibles, &nbSommetsDisponibles);
    printf("\nSommets disponibles :\n\n");
    for (int i = 0; i < nbSommetsDisponibles; ++i) {
        printf("%d ", sommetsDisponibles[i]);
    }

    float duree_max_niveau = 0;

    //descente_graphe(sommetsDisponibles, nbSommetsDisponibles, niveau, graphe->nbSommet, list_sommets, graphe->nbSommet, duree_operations, duree_max_niveau);


    //free(incompatibilites);
    free(num_operations);
    free(duree_operations);

    //free(sommetsDepart);
    free(graphe);
    //free(matriceNiveaux);
    return 0;
}