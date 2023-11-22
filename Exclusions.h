//
// Created by noeld on 19/11/2023.
//

#ifndef PROJETTG_EXCLUSIONS_H
#define PROJETTG_EXCLUSIONS_H

typedef struct {
    int sommet1;
    int sommet2;
} t_paireExclusion;

typedef struct {
    t_paireExclusion* paires;
    int nb_paires;
} t_exclusion;

t_exclusion* lireExclusions();
void descendreNiveauxSuivants(int*** matriceNiveaux, int* niveau, int nbSommet, int niveauInMat, int sommetADescendre);
void comparerExclusionsAvecMatriceNiveaux(int*** matriceNiveaux, int* niveau, int nbSommet, t_exclusion* exclusions);
void afficherPaires(t_exclusion* exclusions);
int sont_incompatibles(int sommet1, int sommet2, t_exclusion* exclusions);

#endif //PROJETTG_EXCLUSIONS_H
