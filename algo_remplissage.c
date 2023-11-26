//
// Created by Gabriel Gasnier on 18/11/2023.
// Copyright (c) 2023 All rights reserved.
//

#include "algo_remplissage.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>




// on créé un graphe a partir de la matrice de niveau et on le rempli avec les opérations tant que la somme de leur poid sur une meme ligne est inférieur a 10
void descente_graphe(Sommet ** MatriceNiveaux,int nbSommet){
    struct File* file = creerFile(nbSommet);
    file->elements[0] = MatriceNiveaux[0][0];
}


