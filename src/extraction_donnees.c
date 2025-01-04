#include <stdio.h>
#include <string.h>
#include "extraction_donnees.h"

/*conversion du risque du patient en un reel (qui joue le rôle de booleen)*/
double conversion_risk(char *risk){
    if (!strcmp(risk, "False")){
       return 0.; 
    }
    else{
        return 1.;
    }
}

// Fonctions permettant d'extraire  les valeurs d'une caractéristique précise (désignée par son identifiant id_carac) à partir d'une structure de type patient

/*Convention id_carac: 1 -> id, 2 -> physical_activity, 3 -> alcohol_consumption, 4 -> caffeine_consumption, 5 -> sleep_quality,  6 -> risk */ 

// Pour l'identifiant des patients
int extraction_id_patient(patient p, int id_carac){ 
    switch (id_carac){
        case 1:
            return p.id;
        default :
            printf("Erreur : identifiant de donnée invalide (%d).\n", id_carac);
            return -1.0;
    }
}

// Pour le reste des caractéristiques
double extraction_donnees(patient p, int id_carac){ 
    switch (id_carac){
        case 2 :                          
            return p.physical_activity;                 // Extraction du niveau d'activité physique 
        case 3 :
            return p.alcohol_consumption;              // Extraction du taux de consommation d'alcool
        case 4 : 
            return p.caffeine_consumption;              //  Extraction du taux de consommation de caffeine
        case 5: 
            return p.sleep_quality;     // Extraction de la qualité du sommeil
        case 6:
            return conversion_risk(p.risk); // Extraction de l'état de risque (0: False, 1: True)
        default:
            printf("Erreur : identifiant de donnée invalide (%d).\n", id_carac);
            return -1.0;
    }
}