#include "normalisation.h"
#include "extraction_donnees.h"

/*fonction qui  calcule le minimum des caratéristiques pour l'ensemble des patients contenus dans une structure lp et retourne le résultat dans un tableau:  
    - liste_patients lp: structure contenant les patients et leur caractéristiques,
    - int nombre_patients_lp : Nombre de patients dans la structure lp,
    - int liste_id_caract[]: Tableau contenant les identifiants de caractéristiques dont on veut calculer le minimum
    - int nbre_caract: nombre de caractéristiques dans liste_id_caract[]
    - double tableau_minimum[]: Tableau contenant le minimum de chacune des caractéristques mentionnées dans liste_id_caract[]*/

void minimum_lp(liste_patients lp, int nombre_patients_lp, int liste_id_caract[], int nbre_caract, double tableau_minimum[]){
        double minimum; 
        for(int i = 0; i < nbre_caract; i ++){                                      // Pour chacune des caractéristiques listées
            minimum = extraction_donnees(lp.liste[0],liste_id_caract[i]);           // Initialisation du minimum à la valeur de la caractéristique pour le premier patient                   
            for (int j = 1; j < nombre_patients_lp; j ++){                             // Pour chaque patient
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


/*fonction qui  calcule le maximum des caratéristiques pour l'ensemble des patients contenus dans une structure lp et retourne le résultat dans un tableau:  
    - liste_patients lp: structure contenant les patients et leur caractéristiques,
    - int nombre_patients_lp : Nombre de patients dans la structure lp,
    - int liste_id_caract[]: Tableau contenant les identifiants de caractéristiques sdont on veut calculer le maximum
    - int nbre_caract: nombre de caractéristiques dans liste_id_caract[]
    - double tableau_maximum[]: Tableau contenant le minimum de chacune des caractéristques mentionnées dans liste_id_caract[]*/

void maximum_lp(liste_patients lp, int nombre_patients_lp, int liste_id_caract[], int nbre_caract, double tableau_maximum[]){
        double maximum; 
        for(int i = 0; i < nbre_caract; i ++){                                      // Pour chacune des caractéristiques listées
            maximum = extraction_donnees(lp.liste[0],liste_id_caract[i]);           // Initialisation du maximum à la valeur de la caractéristique pour le premier patient                   
            for (int j = 1; j < nombre_patients_lp; j ++){                             // Pour chaque patient
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
/*Fonction qui normalise les valeurs de caractéristiques des patients contenus dans la structure lp à partir des données sur les maximum et minimum de chacune des caractéristiques
et les range dans un tableau" 
    - liste_patients lp: structure contenant les patients et leur caractéristiques,
    - int nombre_patients_lp : Nombre de patients dans la structure lp,
    - int liste_id_caract[]: Tableau contenant les identifiants de caractéristiques dont on veut normaliser les valeurs
    - int nbre_caract: nombre de caractéristiques dans liste_id_caract[]
    - double tableau_maximum[]: Tableau contenant le minimum de chacune des caractéristques mentionnées dans liste_id_caract[]
    - double param_lifestyle_norm[][nbre_param] : Tableau contenant par ligne les valeurs normalisées des caractéristiques de chaque patient*/

void normalisation(liste_patients lp, int nombre_patients_lp, int liste_id_caract[], int nbre_caract, double tableau_minimum[], double tableau_maximum[], double param_lifestyle_norm[][nbre_param]){
    for (int i =0; i < nombre_patients_lp; i++){ // Pour chaque patient de lp
        patient p = lp.liste[i];
        for(int j =0; j < nbre_caract; j++){ // pour chaque caractéristique de style de vie
            double valeur_non_norm = extraction_donnees(p, liste_id_caract[j]);  // valeur non normalisée
            double valeur_norm = (valeur_non_norm - tableau_minimum[j]) / (tableau_maximum[j] - tableau_minimum[j]);  // valeur normalisée
            param_lifestyle_norm[i][j] = valeur_norm;   // remplissage de la valeurs de valeurs normalisées
        }
    }
}


/*Fonction qui permet de dénormaliser (remise à l'échelle) les coordonnées des centroides
- coordonnees_centroides[][nbre_param] : Tableau contenant les coordonnées des centroides
- tableau_minimum[] : Tableau contenant les minimum
- tableau_maximum[] : Tableau contenant les maximum
- K : nombre de centroides
*/

void denormaliser_centroides(double coordonnees_centroides[][nbre_param], double tableau_minimum[], double tableau_maximum[], int K){
    for(int i = 0; i < K; i++){
        for (int j = 0; j < nbre_param; j++){
            coordonnees_centroides[i][j] = coordonnees_centroides[i][j] * (tableau_maximum[j] - tableau_minimum[j]) + tableau_minimum[j];
        }
    }
}