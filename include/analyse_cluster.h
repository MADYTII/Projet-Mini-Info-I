#ifndef ANALYSE_CLUSTER_H
#define ANALYSE_CLUSTER_H
#include "types_struct.h"


/*Fonction, qui pour un cluster fait le décompte du nombre de patients à risque "False" et ceux à risque "True"
- lp : structure de type liste_patients contenant à partir de laquelle sont récupérés les états de risque
- cluster[] : Tableau contenant les positions dans lp des patients membres du cluster
- taille cluster : nombre d'éléments dans le cluster
- nbre_true : pointeur faisant référence au nombre de patients à risque "True"
- nbre_false : pointeur faisant référence au nombre de patients à risque "False"
*/

void decompte_true_false (liste_patients lp, int cluster[], int taille_cluster, int *nbre_true, int *nbre_false);

/*Fonction, qui pour un cluster renseigne sur le caractère homogène ou hétérogène des état de risque des patients qui le constituent
- taille cluster : nombre d'éléments dans le cluster
- nbre_true :  nombre de patients à risque "True"
- nbre_false :  nombre de patients à risque "False"
*/
const char *etat_risque_cluster(int nbre_true, int nbre_false, int taille_cluster);


/* Fonction qui retourne le nom de la caractéristique en fonction de son id_carac */
//*Convention id_carac: 1 -> id, 2 -> physical_activity, 3 -> alcohol_consumption, 4 -> caffeine_consumption, 5 -> sleep_quality,  6 -> risk */

const char* nom_caracteristique(int id_carac);



#endif /* ANALYSE_CLUSTER_H*/