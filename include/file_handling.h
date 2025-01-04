#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H
#include "types_struct.h"

// Fonction qui compte le nombre de lignes dans un fichier
int longueur_fichier(char *nom_fichier);

/*Fonction qui extrait et range dans des tableaux, les identifiants de patients et leur statut "risk" à partir du fichier patients.pengu

-char *nom_fichier : chaîne de caractères représentant le nom du fichier à ouvrir
- int id_patients_risk[]:  Tableau d'entier devant recevoir dans l'ordre de lecture, les identifiants des patients dans le fichier
- char risques_patients_risk[][6] : Tableau de chaînes de caractères contenant dans l'odre de lecture du fochier, le niveau de risque des patients
- int nombre_patients_risk : Nombre de patients dans le fichier lu*/

void id_risk (char *nom_fichier, int id_patients_risk[], char risques_patients_risk[][6], int nombre_patients_risk);


/*Lecture des informations concernant le style de vie des patients et chargement dans une structure de type liste_patients
- liste_patients *lp:  pointeur sur la structure à remplir
- char *nom_fichier : Nom du fichier dont on extrait les paramètres de style de vie
- nombre_effectif_patients : Nombre effectif de patients à lire à partir du  fichier*/

void charger_lifestyle(liste_patients *lp, char *nom_fichier, int nombre_effectif_patients);

/* Récupération des données sur l'état de risque  des patients de "lifestyle.pengu" à partir des vecteurs  des id et des risques de tous les patients, tirés de "patients.pengu"
- liste_patients *lp:  pointeur sur la structure à remplir
- nbre_patients_lp : Nombre  de patients dans la structure lp
- int id_patients_risk[] : Tableau contenant les identifiants des patients
- char risques_patients_risk[][6] : Tableau contenant dans l'ordre, les risques des patients dont l'identifiant est dans id_patients_risk[]
- int nombre_patients_risk : Nombre de patients dans id_patients_risk[] */

void charger_risk(liste_patients *lp, int nbre_patients_lp, int id_patients_risk[], char risques_patients_risk[][6], int nombre_patients_risk);

#endif /* FILE_HANDLING_H */