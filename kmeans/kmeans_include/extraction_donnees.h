#ifndef EXTRACTION_DONNEES_H
#define EXTRACTION_DONNEES_H
#include "types_struct.h"

/*conversion du risque du patient en un reel (qui joue le rôle de booleen)*/
double conversion_risk(char *risk);

// Fonctions permettant d'extraire  les valeurs d'une caractéristique précise (désignée par son identifiant id_carac) à partir d'une structure de type patient

/*Convention id_carac: 1 -> id, 2 -> physical_activity, 3 -> alcohol_consumption, 4 -> caffeine_consumption, 5 -> sleep_quality,  6 -> risk */ 

// Pour l'identifiant des patients
int extraction_id_patient(patient p, int id_carac);

// Pour le reste des caractéristiques
double extraction_donnees(patient p, int id_carac);

#endif /* EXTRACTION_DONNEES_H */