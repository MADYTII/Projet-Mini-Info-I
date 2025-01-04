#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "file_handling.h"

// Fonction qui compte le nombre de lignes dans un fichier
int longueur_fichier(char *nom_fichier) {
    FILE *fp = fopen(nom_fichier, "r");
    if (fp == NULL) {
        printf("Erreur d'ouverture de fichier\n");
        exit (1); /*pour renvoyer un message d'erreur*/
    }
    int nombre_lignes = 0;
    char ligne[400]; // tableau devant recevoir le contenu d'une ligne

    while (fgets(ligne, sizeof(ligne), fp) != NULL) {
        nombre_lignes ++;     // Incrémentation du nombre, tant qu'il y en a une qui est lue
    }
    fclose(fp);
    return nombre_lignes;
}

/*Fonction qui extrait et range dans des tableaux, les identifiants de patients et leur statut "risk" à partir du fichier patients.pengu

-char *nom_fichier : chaîne de caractères représentant le nom du fichier à ouvrir
- int id_patients_risk[]:  Tableau d'entier devant recevoir dans l'ordre de lecture, les identifiants des patients dans le fichier
- char risques_patients_risk[][6] : Tableau de chaînes de caractères contenant dans l'odre de lecture du fochier, le niveau de risque des patients
- int nombre_patients_risk : Nombre de patients dans le fichier lu*/

void id_risk (char *nom_fichier, int id_patients_risk[], char risques_patients_risk[][6], int nombre_patients_risk){
    FILE *fp = fopen(nom_fichier, "r"); //  Ouverture du fichier
    if (fp == NULL){
        printf("Erreur d'ouverture de fichier\n");
        exit (1); /*pour renvoyer un message d'erreur*/
    }
    char tampon[300];
    fgets(tampon, sizeof(tampon), fp); //Lecture des en-têtes 

    //Stockage des id et risques dans les tableaux prévus à cet effet
    int i = 0;
    while ( i < nombre_patients_risk && fscanf(fp, "%*d$%d$%*f$%*c$%*f$%*f$%*f$%*f$%*f$%s", &id_patients_risk[i], risques_patients_risk[i]) == 2){
        i++;
    }
    fclose(fp);
}


/*Lecture des informations concernant le style de vie des patients et chargement dans une structure de type liste_patients
- liste_patients *lp:  pointeur sur la structure à remplir
- char *nom_fichier : Nom du fichier dont on extrait les paramètres de style de vie
- nombre_effectif_patients : Nombre effectif de patients à lire à partir du  fichier*/

void charger_lifestyle(liste_patients *lp, char *nom_fichier, int nombre_effectif_patients){
    FILE *fp = fopen(nom_fichier, "r");
    if (fp == NULL){
        printf("Erreur d'ouverture de fichier\n");
        exit (1); /*pour renvoyer un message d'erreur*/
    }
    else{
        /*on doit ignorer la première ligne du fichier étant donné qu'il s'agit d'en-têtes*/
        char tampon[300];                        /* Contiendra les en-têtes*/ 
        fgets(tampon, sizeof(tampon), fp);       // Ignorer les en-têtes
        int i = 0;
        /*variables intermédiaires devant contenir les données extraites du fichier patients.pengu*/
        int id; // Identifiant des patients
        double physical_activity, alcohol_consumption, caffeine_consumption, sleep_quality; // paramètres de style de vie
        while ( i < nombre_effectif_patients && 
        fscanf(fp, "%*d$%d$%lf$%lf$%lf$%lf",&id, &physical_activity, &alcohol_consumption, &caffeine_consumption, &sleep_quality) == 5){
            (*lp).liste[i].id = id; 
            (*lp).liste[i].physical_activity = physical_activity;
            (*lp).liste[i].alcohol_consumption = alcohol_consumption;
            (*lp).liste[i].caffeine_consumption = caffeine_consumption;
            (*lp).liste[i].sleep_quality = sleep_quality;
            i++;
        }
        fclose(fp);
    }
}

/* Récupération des données sur l'état de risque  des patients de "lifestyle.pengu" à partir des vecteurs  des id et des risques de tous les patients, tirés de "patients.pengu"
- liste_patients *lp:  pointeur sur la structure à remplir
- nbre_patients_lp : Nombre  de patients dans la structure lp
- int id_patients_risk[] : Tableau contenant les identifiants des patients
- char risques_patients_risk[][6] : Tableau contenant dans l'ordre, les risques des patients dont l'identifiant est dans id_patients_risk[]
- int nombre_patients_risk : Nombre de patients dans id_patients_risk[] */

void charger_risk(liste_patients *lp, int nbre_patients_lp, int id_patients_risk[], char risques_patients_risk[][6], int nombre_patients_risk){
    //Remplissage des risques des patients dans la structure lp
    for(int i = 0; i < nbre_patients_lp; i++){ // Pour chaque patient dans la structure
        for(int j=0; j < nombre_patients_risk; j++){ 
            if((*lp).liste[i].id == id_patients_risk[j]){   // Si l'identifiant du patient en cours = identifinat d'un patient dans le tableau id_patients_risk
                strcpy((*lp).liste[i].risk, risques_patients_risk[j]); // Affectation du risque correspondant
                break;
            }
        }
    }
}