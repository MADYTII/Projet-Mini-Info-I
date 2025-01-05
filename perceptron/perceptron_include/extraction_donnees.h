#ifndef EXTRACTION_DONNEES_H
#define EXTRACTION_DONNEES_H
#include "types_struct.h"

/*Conversion du sexe en un reel (qui joue le rôle de booleen), 
0 -> M , 1 -> F
nécessaire pour les calculs du perceptron*/
double conversion_sex (char sex); 


/*conversion du risque du patient en un reel (qui joue le rôle de booleen), 
0 -> False , 1 -> True
necessaire pour les calculs du perceptron*/
double conversion_risk(char *risk);


// Fonctions permettant d'extraire à partir  les valeurs d'une caractéristique précise (désignée par son identifiant id_caract) à partir d'une structure de type patient

/*Convention id_carac: 1 -> id, 2 -> age, 3 -> sex, 4 -> weight, 5 -> blood_pressure,  6 -> average_heart_rate, 7 -> blood_sugar, 8 -> cholesterol , 9 -> risk */ 

// Pour l'identifiant des patients
int extraction_id_patient(patient p, int id_carac);


// Pour le reste des caractéristiques
double extraction_donnees(patient p, int id_carac);


#endif /*EXTRACTION_DONNEES_H*/