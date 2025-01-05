#ifndef NORMALISATION_H
#define NORMALISATION_H
#include "types_struct.h"

/*fonction qui prend en entrées:  
    -une structure de type liste_patients qui contient des données sur des patients "lp",
    -le nombre de patients "nombre_patients",
    -un tableau contenant des identifiants de caractéristiques sur ces patients "liste_id_caract[]"
    -le nombre de caractéristiques en question "nbre_caract"
    -et retourne dans un tableau tableau_minimum, fourni en paramètre, les minimum de chacune de ces caractéristiques pour les patients de lp */
void minimum(liste_patients lp, int nombre_patients, int liste_id_caract[], int nbre_caract, double tableau_minimum[]);

/*fonction qui prend en entrées:  
    -une structure de type liste_patients qui contient des données sur des patients "lp",
    -le nombre de patients "nombre_patients",
    -un tableau contenant des identifiants de caractéristiques sur ces patients "liste_id_caract[]"
    -le nombre de caractéristiques en question "nbre_caract"
    -et retourne dans un tableau tableau_maximum, fourni en paramètre, les maximum de chacune des caractéristiques pour les patients de lp */
void maximum(liste_patients lp, int nombre_patients, int liste_id_caract[], int nbre_caract, double tableau_maximum[]);

/*Fonction qui modfie pour un patient, la valeur d'une caractéristique dont l'identifiant est précisé, par une valeur donnée*/
/*Convention id_carac: 1 -> id, 2 -> age, 3 -> sex, 4 -> weight, 5 -> blood_pressure,  6 -> average_heart_rate, 7 -> blood_sugar, 8 -> cholesterol , 9 -> risk */
//Ne concerne que les caractéristiques non booléennes
void modifier_caracteristique_patient(patient *p, int id_carac, double nouvelle_valeur);


/* Fonction qui pour une liste de patients lp, réalise la standardisation par calcul de Z-score des valeurs de différentes caractéristiques*/
// liste_patients *lp : pointeur sur la liste des patients concernés
//int nombre_patients : nombre de patients dans la liste lp
//int liste_id_caract[] : tableau des identifianst des caractéristiques à standardiser
//int nbre_caract : nombre de caractéristiques à standardiser
// double tableau_minimum[] : tableau des minimum associés à  chacune des caractéristiques
// double tableau_maximum[] : tableau des maximum  associés à  chacune des caractéristiques
void normalisation (liste_patients *lp, int nombre_patients, int liste_id_caract[], int nbre_caract, double tableau_minimum[], double tableau_maximum[]);


#endif /*NORMALISATION_H*/