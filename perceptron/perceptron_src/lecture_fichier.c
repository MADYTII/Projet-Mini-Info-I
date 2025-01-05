#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lecture_fichier.h"




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

/*Fonction de lecture du fichier  "patients.pengu"
- liste_patients *lp : pointeur sur la structure à remplir
- char *nom_fichier : chaines de caractères repséentant le nom du fichier à lire, ici "patients.pengu"
- int nbre_patients : nombre de patients à lire*/
void charger_fichier(liste_patients *lp, char *nom_fichier, int nbre_patients){
    FILE *fp = fopen(nom_fichier, "r");
    if (fp == NULL){
        printf("Erreur d'ouverture de fichier\n");
        exit (1); /*pour renvoyer un message d'erreur*/
    }
    else{
        /*on doit ignorer la première ligne du fichier étant donné qu'il s'agit d'en-têtes*/
        char tampon[300];
        fgets(tampon, sizeof(tampon), fp); /*Cette variable sera libérée de la mémoire en sortie de procédure*/
        int i = 0;
        /*variables intermédiaires devant contenir les données extraites du fichier patiens.pengu*/
        int index_; //variable tampon qui sert à enregistrer les valeurs en première colonne (index de ligne)
        int id;
        double age, weight, blood_pressure, average_heart_rate, blood_sugar, cholesterol;
        char sex;
        char risk[6];
        while ( i < nbre_patients && 
        fscanf(fp, "%d$%d$%lf$%c$%lf$%lf$%lf$%lf$%lf$%s",&index_, &id, &age, &sex, &weight, &blood_pressure, &average_heart_rate, &blood_sugar, &cholesterol, risk) == 10){
            (*lp).liste[i].id = id; 
            (*lp).liste[i].age = age;
            (*lp).liste[i].sex = sex;
            (*lp).liste[i].weight = weight;
            (*lp).liste[i].blood_pressure = blood_pressure;
            (*lp).liste[i].average_heart_rate = average_heart_rate;
            (*lp).liste[i].blood_sugar = blood_sugar;
            (*lp).liste[i].cholesterol = cholesterol;
            strcpy((*lp).liste[i].risk, risk);
            i++;
        }
        fclose(fp);
    }
    
}