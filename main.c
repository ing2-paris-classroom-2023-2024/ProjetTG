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
    }
}

int main(){

    struct Graph* graphe = initGraph();
    int nbOperations = nb_operations();
    float cycle = lire_cycle();
    t_exclusion * exclusions = lireExclusions();

    ///Partie du projet lorsque nous avions mal interprété le sujet
    ///Toutes les variabes avec Demo sont dédidés à montrer notre avancement lorsque nous nous étions trompé
    ///Nous avions compris que si 1 était précédent à 2 il devait se trouvé dans la station au dessus
    int* num_operationsDemo = malloc(graphe->nbSommet * sizeof(int));
    float* duree_operationsDemo = malloc(graphe->nbSommet * sizeof(float));
    int* num_operations = malloc(graphe->nbSommet * sizeof(int));
    float* duree_operations = malloc(graphe->nbSommet * sizeof(float));
    int nb_sommets_depart=0;
    int * sommetsDepart = TrouverSommetsDepart(graphe, &nb_sommets_depart);

    init_operationsDemo(nbOperations, num_operationsDemo, duree_operationsDemo);
    init_operations(nbOperations, num_operations, duree_operations);

    int **matriceNiveauxDemo;
    float* poidsNiveauxDemo = malloc(graphe->nbSommet * sizeof (float ));
    int *niveauDemo = CreerMatriceNiveaux(graphe,  nb_sommets_depart, &matriceNiveauxDemo,sommetsDepart);

    comparerExclusionsAvecMatriceNiveaux(graphe, &matriceNiveauxDemo,niveauDemo, graphe->nbSommet, exclusions);
    calculerPoidsNiveaux(&matriceNiveauxDemo, niveauDemo, nbOperations, duree_operationsDemo,poidsNiveauxDemo, cycle, *graphe);

    printf("\n****Matrice Niveau***\n");
    printMatriceNiveaux(matriceNiveauxDemo, graphe->nbSommet, *niveauDemo);
    printf("\n****Poids des Niveaux***\n");
    for(int i=0; i<(*niveauDemo); i++){
        printf("\nStation : %d   poids :  %f",i+1, poidsNiveauxDemo[i]);
    }

    free(matriceNiveauxDemo);
    free(poidsNiveauxDemo);
    free(niveauDemo);
    free(num_operationsDemo);
    free(duree_operationsDemo);




    ///Partie du code dédié au projet
    int **matriceNiveaux;
    float* poidsNiveaux = malloc(graphe->nbSommet * sizeof (float ));
    int *niveau = CreerMatriceNiveaux(graphe,  nb_sommets_depart, &matriceNiveaux,sommetsDepart);
    printf("\n\nnouvelle matrice\n");
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