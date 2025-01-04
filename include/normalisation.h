#ifndef NORMALISATION_H
#define NORMALISATION_H
#include "types_struct.h"


/*fonction qui  calcule le minimum des caratéristiques pour l'ensemble des patients contenus dans une structure lp et retourne le résultat dans un tableau:  
    - liste_patients lp: structure contenant les patients et leur caractéristiques,
    - int nombre_patients_lp : Nombre de patients dans la structure lp,
    - int liste_id_caract[]: Tableau contenant les identifiants de caractéristiques dont on veut calculer le minimum
    - int nbre_caract: nombre de caractéristiques dans liste_id_caract[]
    - double tableau_minimum[]: Tableau contenant le minimum de chacune des caractéristques mentionnées dans liste_id_caract[]*/

void minimum_lp(liste_patients lp, int nombre_patients_lp, int liste_id_caract[], int nbre_caract, double tableau_minimum[]);

/*fonction qui  calcule le maximum des caratéristiques pour l'ensemble des patients contenus dans une structure lp et retourne le résultat dans un tableau:  
    - liste_patients lp: structure contenant les patients et leur caractéristiques,
    - int nombre_patients_lp : Nombre de patients dans la structure lp,
    - int liste_id_caract[]: Tableau contenant les identifiants de caractéristiques sdont on veut calculer le maximum
    - int nbre_caract: nombre de caractéristiques dans liste_id_caract[]
    - double tableau_maximum[]: Tableau contenant le minimum de chacune des caractéristques mentionnées dans liste_id_caract[]*/

void maximum_lp(liste_patients lp, int nombre_patients_lp, int liste_id_caract[], int nbre_caract, double tableau_maximum[]);

/*Fonction qui normalise les valeurs de caractéristiques des patients contenus dans la structure lp à partir des données sur les maximum et minimum de chacune des caractéristiques
et les range dans un tableau" 
    - liste_patients lp: structure contenant les patients et leur caractéristiques,
    - int nombre_patients_lp : Nombre de patients dans la structure lp,
    - int liste_id_caract[]: Tableau contenant les identifiants de caractéristiques dont on veut normaliser les valeurs
    - int nbre_caract: nombre de caractéristiques dans liste_id_caract[]
    - double tableau_maximum[]: Tableau contenant le minimum de chacune des caractéristques mentionnées dans liste_id_caract[]
    - double param_lifestyle_norm[][nbre_param] : Tableau contenant par ligne les valeurs normalisées des caractéristiques de chaque patient*/

void normalisation(liste_patients lp, int nombre_patients_lp, int liste_id_caract[], int nbre_caract, double tableau_minimum[], double tableau_maximum[], double param_lifestyle_norm[][nbre_param]);

/*Fonction qui permet de dénormaliser (remise à l'échelle) les coordonnées des centroides
- coordonnees_centroides[][nbre_param] : Tableau contenant les coordonnées des centroides
- tableau_minimum[] : Tableau contenant les minimum
- tableau_maximum[] : Tableau contenant les maximum
- K : nombre de centroides
*/

void denormaliser_centroides(double coordonnees_centroides[][nbre_param], double tableau_minimum[], double tableau_maximum[], int K);

#endif /* NORMALISATION_H */
