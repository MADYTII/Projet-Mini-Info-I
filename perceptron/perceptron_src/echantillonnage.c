#include <stdlib.h>
#include <string.h>
#include "echantillonnage.h"



// Mélanger les valeurs d'un tableau d'entiers de taille "taille_tableau" selon l'algorithme de Fisher Yates Knuth

void melanger_tableau_FYK (int tableau[], int taille_tableau){
    srand(42);                                     // on s'assure que les tirages aléatoires restent identiques à chaque exécution
    for(int j = taille_tableau - 1; j > 0; j--){
        int indice_aleatoire = rand()%(j+1);              // indice aléatoire entre 0 et j : première et dernière positions de la fenêtre explorée sur le tableau
        int derniere_valeur = tableau[j];              // stockage de la dernière valeur de la fenêtre du tableau explorée
        // échange entre la valeur présente à l'indice aléatoire et le dernier élément de la fenêtre explorée
        tableau[j] = tableau[indice_aleatoire];
        tableau[indice_aleatoire] = derniere_valeur;   
    }
}

// repartition des valeurs d'un tableau1 de taille n1 dans deux sous tableaux (tableau2 et tableau3) de taille n2 et n3 respectivement

void repartition_valeurs(int tableau1[], int tableau2[], int tableau3[], int n1, int n2, int n3){
    //Remplissage du tableau2 par les n2 premiers éléments du tableau 1
    for(int i = 0; i < n2; i++){  
        tableau2[i] = tableau1[i];
    }
    //Remplissage du tableau3 par les n3 derniers éléments du tableau 1
    for (int i = 0; i < n3; i++){
        tableau3[i] = tableau1[i + n2];
    }
}

/*Procédure de remplissage d'une structure de type liste_patients (lp_a_remplir) avec les informations des patients, tirés d'une structure mère lp, 
    les identifiants des patients (dans un tableau) et leur nombre étant précisés*/

void remplir_liste_patients (liste_patients lp, liste_patients *lp_a_remplir, int liste_id_patients[], int nombre_patients){
        for(int i = 0; i < nombre_patients; i++){
            int id_patient = liste_id_patients[i];
            (*lp_a_remplir).liste[i].id = liste_id_patients[i];
            (*lp_a_remplir).liste[i].age = lp.liste[id_patient - 1].age;
            (*lp_a_remplir).liste[i].sex = lp.liste[id_patient - 1].sex;
            (*lp_a_remplir).liste[i].weight =  lp.liste[id_patient - 1].weight;
            (*lp_a_remplir).liste[i].blood_pressure =  lp.liste[id_patient - 1].blood_pressure;
            (*lp_a_remplir).liste[i].average_heart_rate =  lp.liste[id_patient - 1].average_heart_rate;
            (*lp_a_remplir).liste[i].blood_sugar =  lp.liste[id_patient - 1].blood_sugar;
            (*lp_a_remplir).liste[i].cholesterol =  lp.liste[id_patient - 1].cholesterol;
            strcpy((*lp_a_remplir).liste[i].risk, lp.liste[id_patient - 1].risk);
        }
    }