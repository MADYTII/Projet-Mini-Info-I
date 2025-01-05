#include <stdio.h>
#include <string.h>
#include "extraction_donnees.h"



/*Conversion du sexe en un reel (qui joue le rôle de booleen), 
0 -> M , 1 -> F
nécessaire pour les calculs du perceptron*/
double conversion_sex (char sex){
    if (sex == 'M'){
        return 0.;
    }
    else{
        return 1.;
    }
}

/*conversion du risque du patient en un reel (qui joue le rôle de booleen), 
0 -> False , 1 -> True
necessaire pour les calculs du perceptron*/
double conversion_risk(char *risk){
    if (!strcmp(risk, "False")){
       return 0.; 
    }
    else{
        return 1.;
    }
}




// Fonctions permettant d'extraire à partir  les valeurs d'une caractéristique précise (désignée par son identifiant id_caract) à partir d'une structure de type patient

/*Convention id_carac: 1 -> id, 2 -> age, 3 -> sex, 4 -> weight, 5 -> blood_pressure,  6 -> average_heart_rate, 7 -> blood_sugar, 8 -> cholesterol , 9 -> risk */ 

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
            return p.age;                 // Extraction de l'âge 
        case 3 :
            return conversion_sex(p.sex); // Extraction du sexe et Conversion 
        case 4 : 
            return p.weight;              //  Extraction du poids
        case 5: 
            return p.blood_pressure;     // Extraction de la pression sanguine
        case 6:
            return p.average_heart_rate; // Extraction de la fréquence cardiaque moyenne
        case 7:
            return p.blood_sugar;        // Extraction de la glycémie
        case 8:
            return p.cholesterol;        // Extraction du taux de cholestérol
        case 9:
            return conversion_risk(p.risk); // Extraction du risque et conversion 
        default:
            printf("Erreur : identifiant de donnée invalide (%d).\n", id_carac);
            return -1.0;
    }
}