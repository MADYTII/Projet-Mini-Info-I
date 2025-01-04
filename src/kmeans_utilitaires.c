#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "kmeans_utilitaires.h"

/*Fonction qui 
- pour un tableau d'entiers (int tableau[]) 
- de taille donnée (int taille_tableau), 
- vérifie si l'entier (int élément), 
-ajouté à l'indice (int position) 
 -existe déjà dans les positions précédentes*/ 

int doublon (int tableau[], int taille_tableau, int element, int position){
    // validité de l'indice position
    if (position > taille_tableau - 1 || position < 0){
        printf("Position non valide, dépassement de d'indice\n");
        return -1;
    }
    else{
        for (int i = 0; i < position; i++){
            if (tableau[i] == element){
                return 1;    // retourne 1 si élement trouvé
            }
        }
        return 0;           // retourne 0 si élément non trouvé
    }
}

 /*Fonction qui tire  au hasard K entiers tous différents compris dans un intervalle [0, borne_sup] et les range dans un tableau de taille K 
  - int tableau_entiers[] : Tableau d'ntiers devant recevoir les entiers tirés
  - int K: Nombre d'entiers à tirer
  -  int borne_sup : Borne supérieure de l'intervalle de tirage*/

void entier_aléatoire (int tableau_entiers[], int K, int borne_sup){
    srand(time(NULL));
    // Vérification de la validité des paramètres
    if (K > borne_sup + 1) {  // incompatibilité entre K et borne_sup
        printf("Impossible de générer %d nombres distincts dans l'intervalle [0, %d].\n", K, borne_sup);
        return;  // On ne retorune rien
    }
    tableau_entiers[0] = rand()%(borne_sup + 1);    // On remplit la position 0 du tableau
    for (int i = 1; i < K; i++){                     // Pour les autres positions
        tableau_entiers[i] = rand()%(borne_sup + 1);  // on tire un nombre 
        while (doublon (tableau_entiers, K, tableau_entiers[i], i) == 1){  // Tant que l'élément tiré est déjà présent dans le tableau aux positions précédentes
            tableau_entiers[i] = rand()%(borne_sup + 1);                   // on en tire un nouveau
        }
    } 
}



/*Copie des coordonnées des centroides
- coordonnees_centroides_source[][nbre_param] : Tableau source des coordonnées des centroides
-  double coordonnees_centroides_destination[][nbre_param] : Tableau devant recevoir la copie du tableau précédent
- int K : Nombre de centroides*/ 
void copie_centroides( double coordonnees_centroides_source[][nbre_param], double coordonnees_centroides_destination[][nbre_param], int K){
    for (int i = 0; i < K; i++){ // Pour chaque centroide dans la source
        for(int j = 0; j < nbre_param; j++){ //pour chaque paramètre
            coordonnees_centroides_destination[i][j] = coordonnees_centroides_source[i][j]; // On copie la valeur de la source dans le tableau de destination
        }
    }
}

/*Fonction qui calcule la distance euclidienne entre deux points de l'espace
 - double point1[], point2[] : tableaux de réels représentant des points de l'espace
 - int dimension : Dimension de l'espace dans lequel sont exprimés les coordonnées des deux points*/

double distance_euclidienne(double point1[], double point2[], int dimension){
    double somme_difference_carres = 0; //reçoit la somme des carrés différences des coordonnées deux à deux
    for(int i = 0; i < dimension; i++){
        somme_difference_carres += pow(point1[i] - point2[i], 2);
    }
    double dist_euclid = sqrt(somme_difference_carres);  // distance euclidienne
    return dist_euclid;
}


/*Fonction qui détermine la position du minimum d'un tableau de réels
- tableau[] : Tableau de réels
- taille_tableau : entier représentant la taille du tableau
*/

int pos_min_tableau (double tableau[], int taille_tableau){
     // Initialisation de la valeur minimum et de la position
    double minimum = tableau[0];
    int pos_min = 0;
    // Parcours du tableau pour trouver la position du minimum
    for (int i = 1; i < taille_tableau; i++){
        if (minimum > tableau[i]){
            minimum = tableau[i];
            pos_min = i;
        }
    }
    // Retourne la position du minimum
    return pos_min;
}

/*Fonction qui calcule les coordonnées des nouveaux centroides
- coordonnees_centroides[][nbre_param] : Tableau 2D contenant les coordonnées actuelles des centroides 
- K : Nombre de clusters
- jeu_de_donnees[][nbre_param] : Tableau 2D, contenant par ligne, les coordonnées des patients
- nbre_patients : Nombre de patients dans jeu_de_donnees[][nbre_param]
- indice_membres_clusters [][NBMAX_membres_cluster] : Tableau 2D, contenant par ligne, les indices des patients contenus dans un cluster donné
- nombre_elements_cluster[] : Tableau contenant le nombre d'éléments pour chaque cluster
*/

void nouveaux_centroides (double coordonnees_centroides[][nbre_param], int K, double jeu_de_donnees[][nbre_param], int nbre_patients, int indice_membres_clusters [][NBMAX_membres_cluster], int nombre_elements_cluster[]){
    //Parcours de chaque cluster
    for(int i = 0; i < K; i++){
        //Réinitialisation des coordonnees des du centroide
        for (int m = 0; m < nbre_param; m++){
            coordonnees_centroides[i][m] = 0.;
        }
        //Vérification du fait que le cluster ne soit pas vide
        if(nombre_elements_cluster[i] == 0){
            printf("Cluster vide\n");
            continue;
        }
        // Collecte de la somme des valeurs des coordonnées des membres du cluster 
        for(int j = 0; j < nombre_elements_cluster[i]; j++){
            int indice_patient = indice_membres_clusters[i][j]; // indice du patient dans le cluster en cours
            for(int k = 0; k < nbre_param; k++){
                coordonnees_centroides[i][k] += jeu_de_donnees[indice_patient][k];  // Implémentation de la somme des coordonnées
            }
        }

        // Moyenne des valeurs 
        for( int l = 0; l < nbre_param; l++){
            coordonnees_centroides[i][l] = coordonnees_centroides[i][l] / nombre_elements_cluster[i];
        }

    }
}

/*Fonction du calcul de la distance entre les anciennes et nouvelles valeurs d'un centroide et les range dans un tableau
- coordonnees_centroides_ancien[][nbre_param] : Tableau 2D, contenant par ligne les anciennes valeurs des centroides
- coordonnees_centroides_nouveau[][nbre_param]: TYableau 2D, contenant par ligne les nouvelles valeurs de centroides
- K : Nombre de centroides
- distance_centroide_centroide[]: Tableau contenant dans l'ordre, les distances de chaque centroide par rapport à son ancienne valeur*/

void distance_entre_centroides(double coordonnees_centroides_ancien[][nbre_param], double coordonnees_centroides_nouveau[][nbre_param], int K, double distance_centroide_centroide[]){
    double distance; // distance entre l'ancien et le nouveau centroide
    for(int i = 0; i < K; i++){ //pour chaque centroide
        distance = distance_euclidienne(coordonnees_centroides_ancien[i], coordonnees_centroides_nouveau[i], nbre_param); //calcul de la distance avec l'ancien centroide
        distance_centroide_centroide[i] = distance; // Ajout au tableau des distances
    }
}

/*Fonction qui détermine si toutes les valeurs d'un tableau sont inférieures ou égales à une valeur donnée
- tableau[] : Tableau de réels
- taille : entier -> taille du tableau
- valeur : réel auquel sont comparées les valeurs du tableau*/

int sont_inf (double tableau[], int taille, double valeur){
    int i = 0;
    while(i < taille){
        if(tableau[i] > valeur){ // si un élément du tableau est strictement supérieur à valeur
            return 0; // retourne faux (0)
        }
        i++;
    }
    return 1; // Retourne vrai (1),  si tous les éléments sont inférieurs ou égaux à valeur
}


/*Algorithme de classification K-means
- jeu_de_donnees [][nbre_param] : tableau 2D contenant les données normalisées des patients à classifier, une ligne représentant un patient et ses coordonnées
- nbre_patients : nombre de patients dans le jeu de données à classifier
- coordonnes_centroides[][nbre_param] : tableau contenant par ligne, les coordonnées des centroides
- indice_membres_clusters [K][NBMAX_membres_cluster] :  tableau où chaque ligne désigne un cluster et contient les positions des patients qui en sont membres
- nombre_elements_cluster [] : Tableau contenant dans l'ordre, le Nombre d'éléments par cluster
- K: Nombre de clusters
- Nbre_iterations : Nombre d'itération max en cas de non convergence
- Seuil : Seuil de convergence 
 */
void k_means (double jeu_de_donnees[][nbre_param], int nbre_patients, double coordonnees_centroides[][nbre_param],  int indice_membres_clusters [][NBMAX_membres_cluster], int nombre_elements_cluster [], int K, int Nbre_iterations, double seuil){
    
    int convergence; // Variable permettant d'enregistrer l'état de convergence
    int m = 0; // Compteur pour le nombre d'itérations
    double coordonnees_centroides_ancien[K][nbre_param]; // Tableau 2D devant servir de copie pour les coordonnees de centroides en cours
    do{ 
        copie_centroides(coordonnees_centroides, coordonnees_centroides_ancien, K); // copie des coordonnes des centroides
        
        for (int i = 0; i < K; i++){
            nombre_elements_cluster[i] = 0; // Initialisation du nombre d'élements par cluster à 0. 
        }

        // Clusterisation
        for(int i = 0; i < nbre_patients; i++){ // Pour chaque patients du jeu_de_donnees
            double distance_au_centroide[K]; // vecteur contenant les distances aux centroides du patient en cours (désigné par i) du jeu_de_donnees 
            for (int j = 0; j < K; j++){
                distance_au_centroide[j] = distance_euclidienne(jeu_de_donnees[i], coordonnees_centroides[j], nbre_param); // Récupération des distances aux centroides
            }
            // indice du cluster d'appartenance
            int id = pos_min_tableau (distance_au_centroide, K); // position où se trouve la distance euclidienne minimale
            // Affectation de l'indice du patient en cours à son cluster
            indice_membres_clusters[id][nombre_elements_cluster[id]] = i;
            nombre_elements_cluster[id] += 1; // Incrémentation du nombre d'éléments dans le cluster id
        }
    
        // calcul de nouveaux centroides
        nouveaux_centroides (coordonnees_centroides, K, jeu_de_donnees, nbre_patients, indice_membres_clusters, nombre_elements_cluster);

        //distance des nouveaux centroides à leurs précédentes valeurs
        double distances_centroide_centroide[K]; // Tableau contenant les distances
        distance_entre_centroides(coordonnees_centroides_ancien, coordonnees_centroides, K, distances_centroide_centroide); // Calculm des distances

        //Convergence (toutes les valeurs de distance_centroides doivent être inférieures ou égales au seuil)
        if (sont_inf (distances_centroide_centroide, K, seuil) == 1){ // sont_if -> 1 : si toutes les valeurs sont < = seuil , 0 sinon
            convergence = 1; // 1 : True
        }
        else{
            convergence = 0; // 0: False
        }
        m ++;
    
    } while (m < Nbre_iterations && convergence == 0);
    
    //Vérification de la convergence
    printf("Statut algorithme kmeans: ");
    if (convergence == 0){
        printf("\t Convergence non atteinte\n");
    }
    else{
        printf("\t Convergence atteinte\n");
    }
    
}
