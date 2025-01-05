#ifndef LECTURE_FICHIER_H
#define LECTURE_FICHIER_H
#include "types_struct.h"



// Fonction qui compte le nombre de lignes dans un fichier
int longueur_fichier(char *nom_fichier);

/*Fonction de lecture du fichier  "patients.pengu"
- liste_patients *lp : pointeur sur la structure à remplir
- char *nom_fichier : chaines de caractères repséentant le nom du fichier à lire, ici "patients.pengu"
- int nbre_patients : nombre de patients à lire*/
void charger_fichier(liste_patients *lp, char *nom_fichier, int nbre_patients);

#endif /*LECTURE_FICHIER_H*/
