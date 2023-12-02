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
                k++;
            }
        }
    }
}



void calculerPoidsNiveaux(int*** matriceNiveaux, int* niveau, int nbSommet, float* duree_op, float* poidsNiveaux, float cycle, struct Graph g) {
    for (int i = 0; i < (*niveau); i++) {
        float poids = 0;
        for (int j = 0; j < nbSommet; j++) {
                    int sommet = (*matriceNiveaux)[i][j];
                    if (poids + duree_op[(*matriceNiveaux)[i][j]] > cycle) {
                        descendreNiveauxSuivants(&g,matriceNiveaux,niveau,nbSommet,i,sommet);
                    }else {
                        poids += duree_op[(*matriceNiveaux)[i][j]];
                    }
                }
        poidsNiveaux[i] = poids;
        printf("\n%f", poidsNiveaux[i]);
    }
}


void comparerMatriceAvecTableau(int** matrice, int nbsommets, int* tableau) {
    for (int i = 0; i < nbsommets; i++) {
        for (int j = 0; j < nbsommets; j++){
            int elementMatrice = matrice[i][j];
            int present = 0; // Variable pour indiquer si l'élément est présent dans le tableau
            for (int k = 0; k < nbsommets; k++) {
                if (elementMatrice == tableau[k]) {
                    present = 1;
                    break; // Sort de la boucle dès qu'un élément est trouvé
                }
            }

            if (!present) {
                matrice[i][j] = -1; // Met l'élément à -1 s'il n'est pas présent dans le tableau
            }
        }
    }
}


int main(){

    struct Graph* graphe = initGraph();
    int nbOperations = nb_operations();
    int* num_operations = malloc(graphe->nbSommet * sizeof(int));
    float* duree_operations = malloc(graphe->nbSommet * sizeof(float));
    int nb_sommets_depart=0;
    int * sommetsDepart = TrouverSommetsDepart(graphe, &nb_sommets_depart);

    float cycle = lire_cycle();
    //printf("\n\nOperations :\n\n");

    init_operations(nbOperations, num_operations, duree_operations);
    //print_operations(nbOperations, num_operations, duree_operations);

    int **matriceNiveaux;
    float* poidsNiveaux = malloc(graphe->nbSommet * sizeof (float ));
    int *niveau = CreerMatriceNiveaux(graphe,  nb_sommets_depart, &matriceNiveaux,sommetsDepart);
    //printf("\nMatrice des niveaux :\n\n");



    t_exclusion * exclusions = lireExclusions();
    //comparerExclusionsAvecMatriceNiveaux(graphe, &matriceNiveaux,niveau, graphe->nbSommet, exclusions);
    //printMatriceNiveaux(matriceNiveaux, graphe->nbSommet, *niveau);
    /*printf("\nMatrice des niveaux :\n\n");
    printMatriceNiveaux(matriceNiveaux, graphe->nbSommet, *niveau);
    calculerPoidsNiveaux(&matriceNiveaux, niveau, nbOperations, duree_operations,poidsNiveaux, cycle, *graphe);
    comparerMatriceAvecTableau(matriceNiveaux,nbOperations, num_operations);
    printf("\nMatrice des niveaux avec exclusions :\n\n");
    printMatriceNiveaux(matriceNiveaux, graphe->nbSommet, *niveau);
    for(int i=0; i<(*niveau); i++){
        printf("\n%f", poidsNiveaux[i]);
    }*/
    printf("nouvelle matrice\n\n");
    int** nouvelle_matrice = remplissage_stations(matriceNiveaux, cycle, niveau, duree_operations, num_operations, nbOperations, exclusions);
    printMatriceNiveaux(nouvelle_matrice, graphe->nbSommet, *niveau);

    free(num_operations);
    free(duree_operations);


    free(graphe);
    free(matriceNiveaux);
    free(nouvelle_matrice);
    free(exclusions);
    free(poidsNiveaux);
    free(sommetsDepart);


    return 0;
}