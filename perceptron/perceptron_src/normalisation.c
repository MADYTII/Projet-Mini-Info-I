#include <stdio.h>
#include "normalisation.h"
#include "extraction_donnees.h"


/*fonction qui prend en entrées:  
    -une structure de type liste_patients qui contient des données sur des patients "lp",
    -le nombre de patients "nombre_patients",
    -un tableau contenant des identifiants de caractéristiques sur ces patients "liste_id_caract[]"
    -le nombre de caractéristiques en question "nbre_caract"
    -et retourne dans un tableau tableau_minimum, fourni en paramètre, les minimum de chacune de ces caractéristiques pour les patients de lp */
void minimum(liste_patients lp, int nombre_patients, int liste_id_caract[], int nbre_caract, double tableau_minimum[]){
        double minimum; 
        for(int i = 0; i < nbre_caract; i ++){                                      // Pour chacune des caractéristiques listées
            minimum = extraction_donnees(lp.liste[0],liste_id_caract[i]);           // Initialisation du minimum à la valeur de la caractéristique pour le premier patient                   
            for (int j = 1; j < nombre_patients; j ++){                             // Pour chaque patient
                patient p = lp.liste[j];
                double donnee = extraction_donnees(p,liste_id_caract[i]);
                // Modification du minimum si nécessaire
                if(donnee < minimum){             
                    minimum = donnee;
                }
            }
            tableau_minimum[i] = minimum;                         // Enregistrement du minimum des valeurs de la caractéristique en cours

        }
}



/*fonction qui prend en entrées:  
    -une structure de type liste_patients qui contient des données sur des patients "lp",
    -le nombre de patients "nombre_patients",
    -un tableau contenant des identifiants de caractéristiques sur ces patients "liste_id_caract[]"
    -le nombre de caractéristiques en question "nbre_caract"
    -et retourne dans un tableau tableau_maximum, fourni en paramètre, les maximum de chacune des caractéristiques pour les patients de lp */
void maximum(liste_patients lp, int nombre_patients, int liste_id_caract[], int nbre_caract, double tableau_maximum[]){
        double maximum; 
        for(int i = 0; i < nbre_caract; i ++){                                      // Pour chacune des caractéristiques listées
            maximum = extraction_donnees(lp.liste[0],liste_id_caract[i]);           // Initialisation du maximum à la valeur de la caractéristique pour le premier patient                   
            for (int j = 1; j < nombre_patients; j ++){                             // Pour chaque patient
                patient p = lp.liste[j];
                double donnee = extraction_donnees(p,liste_id_caract[i]);
                // Modification du maximum si nécessaire
                if(donnee > maximum){             
                    maximum = donnee;
                }
            }
            tableau_maximum[i] = maximum;                         // Enregistrement du maximum des valeurs de la caractéristique en cours

        }
}


/*Fonction qui modfie pour un patient, la valeur d'une caractéristique dont l'identifiant est précisé, par une valeur donnée*/
/*Convention id_carac: 1 -> id, 2 -> age, 3 -> sex, 4 -> weight, 5 -> blood_pressure,  6 -> average_heart_rate, 7 -> blood_sugar, 8 -> cholesterol , 9 -> risk */
//Ne concerne que les caractéristiques non booléennes
void modifier_caracteristique_patient(patient *p, int id_carac, double nouvelle_valeur){
    switch (id_carac){
        case 2:
            (*p).age = nouvelle_valeur;
            break;
        case 4:
            (*p).weight = nouvelle_valeur;
            break;
        case 5:
            (*p).blood_pressure = nouvelle_valeur;
            break;
        case 6:
            (*p).average_heart_rate = nouvelle_valeur;
            break;
        case 7:
            (*p).blood_sugar = nouvelle_valeur;
            break;
        case 8:
            (*p).cholesterol = nouvelle_valeur;
            break;
        default:
            printf("Erreur : identifiant de donnée invalide (%d).\n", id_carac);
    }
}

/* Fonction qui pour une liste de patients lp, réalise la standardisation par calcul de Z-score des valeurs de différentes caractéristiques*/
// liste_patients *lp : pointeur sur la liste des patients concernés
//int nombre_patients : nombre de patients dans la liste lp
//int liste_id_caract[] : tableau des identifianst des caractéristiques à standardiser
//int nbre_caract : nombre de caractéristiques à standardiser
// double tableau_minimum[] : tableau des minimum associés à  chacune des caractéristiques
// double tableau_maximum[] : tableau des maximum  associés à  chacune des caractéristiques
void normalisation (liste_patients *lp, int nombre_patients, int liste_id_caract[], int nbre_caract, double tableau_minimum[], double tableau_maximum[]){
    for(int i = 0; i < nbre_caract; i++){                                                           // Pour chaque caractéristique
        if(tableau_maximum[i] - tableau_minimum[i]!=0){
            for(int j = 0; j < nombre_patients; j++){                                                   // Pour chaque patient
                double valeur_non_norm = extraction_donnees((*lp).liste[j],liste_id_caract[i]);         // récupération de la donnée non standardisée
                double valeur_norm = (valeur_non_norm - tableau_minimum[i]) / (tableau_maximum[i] - tableau_minimum[i]);     // Calcul de la donnée normalisée 
                modifier_caracteristique_patient(&(*lp).liste[j], liste_id_caract[i], valeur_norm);     // Modification de la donnée non normalisée par sa valeur normalisée
            }
        }
    }
}