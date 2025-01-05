#ifndef TYPES_STRUCT_H
#define TYPES_STRUCT_H

#include "constantes.h"

/*Structure représentant un patient, les informations sur son style de vie et son statut : à risque ou non*/
typedef struct{
    int id;
    double physical_activity;
    double alcohol_consumption;
    double caffeine_consumption;
    double sleep_quality;
    char risk[6]; // Suffisamment grand pour contenir les valeurs "True" ou "False" + '\0' 
}patient;

/*structure contenant l'ensemble des patients avec les infos sur le tyle de vie et leur état de risque*/
typedef struct {
    patient liste[NBMAX_patients];
} liste_patients;

#endif /* TYPES_STRUCT_H*/