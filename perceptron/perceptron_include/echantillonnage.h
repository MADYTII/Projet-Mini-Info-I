#ifndef ECHANTILLONNAGE_H
#define ECHANTILLONNAGE_H
#include "types_struct.h"
// Mélanger les valeurs d'un tableau d'entiers de taille "taille_tableau" selon l'algorithme de Fisher Yates Knuth

void melanger_tableau_FYK (int tableau[], int taille_tableau);

// repartition des valeurs d'un tableau1 de taille n1 dans deux sous tableaux (tableau2 et tableau3) de taille n2 et n3 respectivement

void repartition_valeurs(int tableau1[], int tableau2[], int tableau3[], int n1, int n2, int n3);


/*Procédure de remplissage d'une structure de type liste_patients (lp_a_remplir) avec les informations des patients, tirés d'une structure mère lp, 
    les identifiants des patients (dans un tableau) et leur nombre étant précisés*/
void remplir_liste_patients (liste_patients lp, liste_patients *lp_a_remplir, int liste_id_patients[], int nombre_patients);

#endif /*ECHANTILLONNAGE_H*/