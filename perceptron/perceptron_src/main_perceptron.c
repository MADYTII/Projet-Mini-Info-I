#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "types_struct.h"         // Bibliothèque pour les structures
#include "lecture_fichier.h"     // Lecture des fichier et remplissage des structures de type
#include "extraction_donnees.h" // extraction de données spécifiques à partir des structures
#include "echantillonnage.h"    // Répartition en ensemble d'entraînement et de test
#include "normalisation.h"     // Normalisation des données
#include "perceptron_utilitaires.h" // calculs du perceptron

int main(){

/*Etape 1: Lecture du fichier et stockage des données des patients dans une structure liste_patients*/

    liste_patients lp;  // initialisation de la strcuture
    char *nom_fichier = "perceptron_data/patients.pengu"; //Fichier à partir duquel on effectue la lecture
    int nbre_patients = longueur_fichier(nom_fichier) - 1; // Nombre de patients dans le fichier "patients.pengu"
    charger_fichier(&lp, nom_fichier, nbre_patients);  //remplissage de la structure l_p*/

/*Etape 2: Echantillonage des patients et répartition en ensembles d'entraînement et de test*/
    
    // 2-1. Récupération des identifiants des patients
    int liste_id_patients[nbre_patients];                        //tableau recevant les id des patients
    
    for (int i = 0; i < nbre_patients; i++){                                
        liste_id_patients[i] = extraction_id_patient(lp.liste[i], 1);   // Remplissage de liste_id_patients
    }
    // 2-2. Mélangeage des id des patients pour que l'inclusion des patients dans les ensembles d'entraînement et de test soit aléatoire
    melanger_tableau_FYK (liste_id_patients, nbre_patients); // Algorithme de Fisher-Yates-Knuth (FYK)

    //2-3 Consititution des ensembles d'entraînement (70% du total des patients) et de de test (80% du total des patients)

    int taille_ensemble_entrainement = 0.7 * nbre_patients;  // taille set d'entrainement
    int taille_ensemble_test = 0.3 * nbre_patients;       // taille set de test
    int id_patients_entrainement[taille_ensemble_entrainement];      // liste des id des patients pour l'ensemble d'entrainement
    int id_patients_test[taille_ensemble_test];                   // liste des id des patients pour l'ensemble de test

    // 2-3-1. Répartition des id des patients en catégories :  entraînement et test
    repartition_valeurs(liste_id_patients, id_patients_entrainement, id_patients_test, nbre_patients, taille_ensemble_entrainement, taille_ensemble_test);
    // 2-3-2. Stockage des informations des patients retenus pour l'entraînement et le test dans des structures liste_patients dédiées
    liste_patients lp_entrainement, lp_test;  // déclaration des structures
    remplir_liste_patients(lp, &lp_entrainement, id_patients_entrainement, taille_ensemble_entrainement); // remplissage de la structure d'entraînement
    remplir_liste_patients(lp, &lp_test, id_patients_test, taille_ensemble_test);                        // remplissage de la structure de test

/*Etape 3 : Normalisation des données : cas des caractéristiques non booléennes*/

    // 3-1 Minimum et maximum pour chacune des caractéristiques non booléennes sur les données d'entraînement
    /*Convention id_caracteristiques: 1 -> id, 2 -> age, 3 -> sex, 4 -> weight, 5 -> blood_pressure,  6 -> average_heart_rate, 7 -> blood_sugar, 8 -> cholesterol , 9 -> risk */
    int nbre_caract_non_bool = 6;                            // Nombre de caractéristiques d'intérêt 
    int liste_id_caract_non_bool [] = {2,4,5,6,7,8};          // Initialisation de la liste contenant les identifiants des caractéristiques à normaliser
    double minimum_caract_non_bool [nbre_caract_non_bool];                    // Tableau des moyennes des caractéristques pour lp_entraînement
    double maximum_caract_non_bool [nbre_caract_non_bool];                // Tableau des écarts-types des caractéristiques  lp_entraînement
    minimum(lp_entrainement, taille_ensemble_entrainement, liste_id_caract_non_bool, nbre_caract_non_bool,  minimum_caract_non_bool); // Moyennes des caractéristiques non booléennes
    maximum(lp_entrainement, taille_ensemble_entrainement, liste_id_caract_non_bool, nbre_caract_non_bool,  maximum_caract_non_bool); // ecarts-types des caractéristiques non booléennes
    
    //3-2 Normalisation des caractéristiques

    // 3-2.1 On standardise l'ensemble d'entrainement par rapport à ses statistiques (minimum: minimum_caract_non_bool  et maximum: maximum_caract_non_bool) 
    normalisation (&lp_entrainement, taille_ensemble_entrainement, liste_id_caract_non_bool, nbre_caract_non_bool, minimum_caract_non_bool, maximum_caract_non_bool);
    
    // 3-2.2 On standardise l'ensemble de test par rapport aux  statistiques de l'ensemble d'entraînement (minimum: minimum_caract_non_bool  et maximum: maximum_caract_non_bool)
    normalisation (&lp_test, taille_ensemble_test, liste_id_caract_non_bool, nbre_caract_non_bool, minimum_caract_non_bool, maximum_caract_non_bool);
    
/*Etape 4: Prédiction*/
    /*Convention id_carac: 1 -> id, 2 -> age, 3 -> sex, 4 -> weight, 5 -> blood_pressure,  6 -> average_heart_rate, 7 -> blood_sugar, 8 -> cholesterol , 9 -> risk */
    int nbre_total_caracteristiques = 7;                       // Nombre total de caractéristiques de classification
    int liste_id_caract_complete [] = {2,3,4,5,6,7,8};         // tableau des id des caractéristiques de classification

    //4-1) Perceptron 2D (à générer pour les couples de caractéristiques allant de l'âge (id_carac = 2) au taux de cholesterol (id_carac = 8))
    // 4-1.1 - Entraînement
    /*Boucle pour générer des perceptrons pour l'ensemble des couples de caractéristiques de liste_id_caract_complete */
    printf("************************************************** PERCEPTRON 2D******************************************************\n");
    int nbre_caract2D = 2; // Nombre de caractéristiques pour une classification 2D
    srand(time(NULL));
    for(int i = 0; i < nbre_total_caracteristiques - 1; i++){
        for(int j = i + 1; j < nbre_total_caracteristiques; j++){
            // collecte des identifiants des caractéristiques
            int id_carac1 = liste_id_caract_complete[i];
            int id_carac2 = liste_id_caract_complete[j];
            int liste_id2D[] = {id_carac1, id_carac2};           // tableau  du couple de caractéristiques pour le perceptron 2D           
            //initialisation des poids (w1, w2) et du biais
            double w1 = ((double)rand()/RAND_MAX ) * 0.002 - 0.001;        // poids caractéristique 1 (id_carac1)
            double w2 = ((double)rand()/RAND_MAX ) * 0.002 - 0.001;        // poids caractéristique 2 (id_carac2)
            double biais = 0.;    // biais
            double poids_biais2D [] = {w1, w2, biais};        // poids_biais = [w1, w2, biais]

            // autres paramètres
            double taux_apprentissage = 0.01;                  // initialisation du taux d'apprentissage
            int Nbre_iterations = 100;                       // nombre d'itérations maximal en cas de non convergence
            
            //entraînement sur l'ensemble d'entrâinement
            printf("Perceptron : %s & %s \n", nom_caracteristique(id_carac1), nom_caracteristique(id_carac2)); // Affichage des caractéristiques en cours
            printf("\t Avant entraînement: w1 = %lf w2 = %f biais = %lf\n", poids_biais2D[0], poids_biais2D[1], poids_biais2D[2]); // Affichage des valeurs initiales de poids et de biais
            perceptron_entrainement(lp_entrainement, taille_ensemble_entrainement, liste_id2D, nbre_caract2D, poids_biais2D, taux_apprentissage,  Nbre_iterations); //Entraînement
            printf("\t Après entraînement: w1 = %lf w2 = %f biais = %lf\n", poids_biais2D[0], poids_biais2D[1], poids_biais2D[2]);   // Affichage des valeurs de poids et de biais à la fin de l'entraînement
            // Taux d'erreur : calculé sur l'ensemble de test
            double taux_erreur = perceptron_test(lp_test, taille_ensemble_test, liste_id2D, nbre_caract2D, poids_biais2D);
            printf("\t Taux d'erreur (ensemble de test) : %lf\n", taux_erreur);         
        } 
    }  
    

    //4-2) Perceptron nD
    //La prédiction est réalisée à partir de toutes les caractéristiques du tableau liste_id_caract_complete
    //Initialisation des poids et du biais
    double poids_biais_nD[nbre_total_caracteristiques + 1]; //  [w1, ...., wn, biais] avec n = nonbre_total_caracteristiques = 7
    for (int i = 0; i < nbre_total_caracteristiques; i++){  
        poids_biais_nD[i] = ((double)rand()/RAND_MAX ) * 0.002 - 0.001;                             //initialisation des poids
    }
    double biais = 0.;
    poids_biais_nD[nbre_total_caracteristiques] = biais;    // biais
    
    //Affichage des poids avant entraînement
    printf("************************************************** PERCEPTRON nD******************************************************\n");
    printf("Avant entrainement:\n");
    for (int i = 0; i < nbre_total_caracteristiques + 1; i++){
        printf("w%d=%lf ", i+1 ,poids_biais_nD[i]);
    }
    printf("biais = %lf\n", poids_biais_nD[nbre_total_caracteristiques]);
    //Autres paramètres
    double taux_apprentissage = 0.01;                  // initialisation du taux d'apprentissage
    int Nbre_iterations = 100;                       // nombre d'itérations maximal en cas de non convergence

    //Entraînement
    perceptron_entrainement(lp_entrainement, taille_ensemble_entrainement, liste_id_caract_complete, nbre_total_caracteristiques, poids_biais_nD, taux_apprentissage,  Nbre_iterations); //Entraînement
    //Affichage des poids après entraînement
    printf("Après entrainement:\n");
    for (int i = 0; i < nbre_total_caracteristiques + 1; i++){
        printf("w%d=%lf ", i+1 ,poids_biais_nD[i]);
    }
    printf("biais = %lf\n", poids_biais_nD[nbre_total_caracteristiques]);

    // Taux d'erreur : calculé sur l'ensemble de test
    double taux_erreur = perceptron_test(lp_test, taille_ensemble_test, liste_id_caract_complete, nbre_total_caracteristiques, poids_biais_nD);
    printf("\t Taux d'erreur %lf\n", taux_erreur); 
    return 0;
}