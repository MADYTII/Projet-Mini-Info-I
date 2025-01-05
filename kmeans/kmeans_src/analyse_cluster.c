#include "analyse_cluster.h"
#include "extraction_donnees.h"

/*Fonction, qui pour un cluster fait le décompte du nombre de patients à risque "False" et ceux à risque "True"
- lp : structure de type liste_patients contenant à partir de laquelle sont récupérés les états de risque
- cluster[] : Tableau contenant les positions dans lp des patients membres du cluster
- taille cluster : nombre d'éléments dans le cluster
- nbre_true : pointeur faisant référence au nombre de patients à risque "True"
- nbre_false : pointeur faisant référence au nombre de patients à risque "False"
*/

void decompte_true_false (liste_patients lp, int cluster[], int taille_cluster, int *nbre_true, int *nbre_false){

    for(int i = 0; i < taille_cluster; i++){
        int position_patient = cluster[i]; //  position du patient du cluster, dans la liste lp
        patient p = lp.liste[position_patient]; // récupération du patient
        double risk = extraction_donnees(p, 6); // risque du patient (0: False, 1: True);  6 -> id_carac de risk
        if (risk == 0.){ // Si risque = "False" (0.)
            (*nbre_false) ++; // incrémentation du nombre de Fasle
        }
        else{
            (*nbre_true) ++; // Incrémentation du nombre de True
        }
    }
}



/*Fonction, qui pour un cluster renseigne sur le caractère homogène ou hétérogène des état de risque des patients qui le constituent
- taille cluster : nombre d'éléments dans le cluster
- nbre_true :  nombre de patients à risque "True"
- nbre_false :  nombre de patients à risque "False"
*/
const char *etat_risque_cluster(int nbre_true, int nbre_false, int taille_cluster){

    if (nbre_false == taille_cluster){  
        return "False (Homogène)"; // (Le risque commun est "False")
    }
    else if(nbre_true == taille_cluster){ //
        return "True (Homogène)"; //(Le risque commun est "True")
    }
    else{                      // Sinon, 
        return "Heterogène"; //les états de risque sont hétérogènes
    }

}


/* Fonction qui retourne le nom de la caractéristique en fonction de son id_carac */
//*Convention id_carac: 1 -> id, 2 -> physical_activity, 3 -> alcohol_consumption, 4 -> caffeine_consumption, 5 -> sleep_quality,  6 -> risk */

const char* nom_caracteristique(int id_carac){
    switch (id_carac) {
        case 1: 
            return "Id";
        case 2: 
            return "Physical activity";
        case 3: 
            return "Alcohol consumption";
        case 4: 
            return "Caffeine_consumption";
        case 5: 
            return "Sleep quality";
        case 6: 
            return "Risk";
        default: 
            return "Inconnu";
    }
}    
