#include <stdio.h>
#include "types_struct.h"
#include "file_handling.h"
#include "normalisation.h"
#include "kmeans_utilitaires.h"
#include "analyse_cluster.h"


int main(){

//Etape 1. Collecte des données sur le style de vie et le niveau de risque des patients
    /*Etape 1-1: Récupération des identifiants des patients et de leur risque dans le fichier patients.pengu*/
    char *nom_fichier1 = "patients.pengu"; // Fichier  patients.pengu
    int nombre_patients_risk = longueur_fichier(nom_fichier1) - 1; // Nombre de patients dans patients.pengu
    int id_patients_risk[nombre_patients_risk];            // Tableau contenant dans l'ordre les identifiants des patients de patients.pengu
    char risques_patients_risk[nombre_patients_risk][6];   // Tableau contenant dans l'ordre les risques des patients de patients.pengu
    id_risk (nom_fichier1, id_patients_risk, risques_patients_risk, nombre_patients_risk); // Collecte des risques et des id de tous les patients de patients.pengu

//Etape 2. Lecture et stockage des informations sur le style de vie des patients

    liste_patients lp;  // initialisation de la structure devant contenir les patients de lifestyle.pengu
    // Style de vie
    char *nom_fichier2 = "lifestyle.pengu"; // Fichier sur le style de vie
    int nbre_patients_lifestyle = longueur_fichier(nom_fichier2) - 1; // Nombre de patients dans le fichier "lifestyle.pengu"
    charger_lifestyle(&lp, nom_fichier2, nbre_patients_lifestyle);  //remplissage des données sur le style de vie
    // Etat de risque
    charger_risk(&lp, nbre_patients_lifestyle, id_patients_risk, risques_patients_risk, nombre_patients_risk);  // remplissage des états de risque pour les patients de lp

//Etape 3. Normalisation des valeurs des paramètres de classification (style de vie)

    // 3-1 Minimum et maximum des paramètres de style de vie
    /*Convention id_carac: 1 -> id, 2 -> physical_activity, 3 -> alcohol_consumption, 4 -> caffeine_consumption, 5 -> sleep_quality,  6 -> risk */

    int nbre_param_lifestyle = nbre_param;                                     // Nombre de caractéristiques d'intérêt (paramètres de style de vie)
    int liste_id_param_lifestyle [] = {2,3,4,5};                              // Initialisation de la liste contenant les identifiants des paramètres de style de vie à normaliser
    double minimum_param_lifestyle [nbre_param_lifestyle];                    // Tableau des minimum des paramètres de style de vie
    double maximum_param_lifestyle [nbre_param_lifestyle];                   // Tableau des maximum des paramètres de style de vie
    minimum_lp(lp, nbre_patients_lifestyle, liste_id_param_lifestyle, nbre_param_lifestyle, minimum_param_lifestyle); //minimum des paramètres de style de vie
    maximum_lp(lp, nbre_patients_lifestyle, liste_id_param_lifestyle, nbre_param_lifestyle, maximum_param_lifestyle);  //maximum  des paramètres de style de vie

    //3-2. Normalisation

    //Les données sont stockées dans un tableau 2D, les lignes représentent les données de chaque patient de lp dans l'ordre de liste_id_param_lifestyle 
    double data_lifestyle_norm [nbre_patients_lifestyle][nbre_param_lifestyle]; //Matrice des valeurs de paramètres de style vie normalisées
    //Remplissage de la matrice précédente à partir des données de la structure lp et des connaissances sur le min et le max de chaque paramètre
    normalisation(lp, nbre_patients_lifestyle, liste_id_param_lifestyle, nbre_param_lifestyle, minimum_param_lifestyle, maximum_param_lifestyle, data_lifestyle_norm); 

// Etape 4. Classification k-means

    int K = 2; // Nombre de clusters
   //Les patients seront désormais référencés par leur indices dans la structure lp de longueur nbre_patients_lifestyle
   
   // 4.1 Choix de centroides initiaux
    int indices_centroides_initiaux [K];  // Tableau devant recevoir les indices des centroides initiaux 
    entier_aléatoire(indices_centroides_initiaux, K, nbre_patients_lifestyle - 1);  // choix aléatoire de centroides 

   //Affichage des patients sélectionnés comme centroides
   printf("Patients sélectionnés comme centroides: \n");
    for(int i = 0; i < K; i++){
         patient p = lp.liste[indices_centroides_initiaux[i]];
         printf("\t Centroide %d, ID_patient = %d, Risk = %s\n", i+1, p.id, p.risk);
    }

   //4.2 Collecte des coordonnées (valeur des paramètres de style de vie) normalisées  des centroides de départ
   double coordonnees_centroides [K][nbre_param_lifestyle]; // Tableau 2D, contenant par ligne, les cordonnées de chacun des K centroides
   for (int i = 0; i < K; i++){
        int indice_centroide = indices_centroides_initiaux[i];  // Indice du centroide
        //récupération des coordonnées normalisées du centroide à partir de la matrice de coordonnées normalisées "param_lifestyle_norm"
        for(int j = 0; j < nbre_param_lifestyle; j++){
            coordonnees_centroides[i][j] = data_lifestyle_norm[indice_centroide][j]; 
            
        }
    }

   //4.3: Classification

   int indice_membres_clusters [K][NBMAX_membres_cluster];  // tableau 2D  à K lignes et NBMAX_membres_cluster colonnes, une ligne contient les positions dans lp, des membres d'un cluster
   int nombre_elements_cluster[K]; // Tableau devant contenir le nombre d'éléments par cluster
   int Nbre_iterations = 100; // Nombre d'itérations
   double seuil = 1e-4; // Seuil permettant de vérifier la convergence de l'algorithme de classification
   k_means (data_lifestyle_norm, nbre_patients_lifestyle, coordonnees_centroides, indice_membres_clusters, nombre_elements_cluster,K, Nbre_iterations, seuil); // Clusterisation

// Etape 5. Caractéristiques des clusters identifiés
   // Le résumé des caractéristiques d'un cluster est contenu dans les coordonnées de son centroide

   // 5.1 Renormalisation des coordonnées des centroides
   denormaliser_centroides(coordonnees_centroides, minimum_param_lifestyle, maximum_param_lifestyle, K); // Remise à l'échelle des centroides

   // 5.2 Affichage des caractéristiques de style de vie  et état de risque par cluster

   int nbre_true, nbre_false;  //  nombres de patients à risque True d'une part et False d'autre part dans un cluster
   
   for (int i = 0; i < K; i++){
        printf("Cluster %d , Nombre de patients : %d \n", i+1, nombre_elements_cluster[i]);   // Cluster Numéro i+1
        // Affichage des caractéristiques du cluster
        printf("\t Caractéristiques: \n");
        for (int j = 0; j < nbre_param; j++){
            printf("\t\t %s = %.2lf\n", nom_caracteristique(liste_id_param_lifestyle[j]), coordonnees_centroides[i][j]);
        }
        // répartition des risques de patient au sein du cluster
        nbre_true = 0;
        nbre_false = 0;
        decompte_true_false(lp, indice_membres_clusters[i], nombre_elements_cluster[i], &nbre_true, &nbre_false); // Décompte des nombre de patients à risque True et False dans le cluster
        printf("\t Répartition du risque : False -> %d patients, True -> %d  patients\n", nbre_false, nbre_true);
        printf("\t Etat de risque : %s\n", etat_risque_cluster(nbre_true, nbre_false, nombre_elements_cluster[i])); // caractère homogène ou hétérogène du risque dans le cluster   
    } 

}