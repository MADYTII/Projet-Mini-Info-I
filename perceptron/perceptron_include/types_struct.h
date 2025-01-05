#ifndef TYPES_STRUCT_H
#define TYPES_STRUCT_H

#define NB_MAXpatients 5000  // Nombre max de patients
/*Structure représentant un patient, ses caractéristiques et son statut : à risque ou non*/
typedef struct{
    int id;
    double age;
    char sex;
    double weight;
    double blood_pressure;
    double average_heart_rate;
    double blood_sugar;
    double cholesterol;
    char risk[6]; // Suffisamment grand pour contenir les valeurs "True" ou "False" + '\0' 
}patient;


/*structure contenant l'ensemble des patients ainsi que leurs informations*/
typedef struct {
    patient liste[NB_MAXpatients];
} liste_patients;

#endif /*TYPES_STRUCT_H*/
