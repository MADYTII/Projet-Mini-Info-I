#ifndef KMEANS_UTILITAIRES_H
#define KMEANS_UTILITAIRES_H
#include "constantes.h"

/*Fonction qui 
- pour un tableau d'entiers (int tableau[]) 
- de taille donnée (int taille_tableau), 
- vérifie si l'entier (int élément), 
- ajouté à l'indice (int position) 
 -existe déjà dans les positions précédentes*/ 

int doublon (int tableau[], int taille_tableau, int element, int position);


 /*Fonction qui tire  au hasard K entiers tous différents compris dans un intervalle [0, borne_sup] et les range dans un tableau de taille K 
  - int tableau_entiers[] : Tableau d'ntiers devant recevoir les entiers tirés
  - int K: Nombre d'entiers à tirer
  -  int borne_sup : Borne supérieure de l'intervalle de tirage*/

void entier_aléatoire (int tableau_entiers[], int K, int borne_sup);


/*Copie des coordonnées des centroides
- coordonnees_centroides_source[][nbre_param] : Tableau source des coordonnées des centroides
-  double coordonnees_centroides_destination[][nbre_param] : Tableau devant recevoir la copie du tableau précédent
- int K : Nombre de centroides*/ 
void copie_centroides( double coordonnees_centroides_source[][nbre_param], double coordonnees_centroides_destination[][nbre_param], int K);

/*Fonction qui calcule la distance euclidienne entre deux points de l'espace
 - double point1[], point2[] : tableaux de réels représentant des points de l'espace
 - int dimension : Dimension de l'espace dans lequel sont exprimés les coordonnées des deux points*/

double distance_euclidienne(double point1[], double point2[], int dimension);


/*Fonction qui détermine la position du minimum d'un tableau de réels
- tableau[] : Tableau de réels
- taille_tableau : entier représentant la taille du tableau
*/

int pos_min_tableau (double tableau[], int taille_tableau);


/*Fonction qui calcule les coordonnées des nouveaux centroides
- coordonnees_centroides[][nbre_param] : Tableau 2D contenant les coordonnées actuelles des centroides 
- K : Nombre de clusters
- jeu_de_donnees[][nbre_param] : Tableau 2D, contenant par ligne, les coordonnées des patients
- nbre_patients : Nombre de patients dans jeu_de_donnees[][nbre_param]
- indice_membres_clusters [][NBMAX_membres_cluster] : Tableau 2D, contenant par ligne, les indices des patients contenus dans un cluster donné
- nombre_elements_cluster[] : Tableau contenant le nombre d'éléments pour chaque cluster
*/

void nouveaux_centroides (double coordonnees_centroides[][nbre_param], int K, double jeu_de_donnees[][nbre_param], int nbre_patients, int indice_membres_clusters [][NBMAX_membres_cluster], int nombre_elements_cluster[]);



/*Fonction du calcul de la distance entre les anciennes et nouvelles valeurs d'un centroide et les range dans un tableau
- coordonnees_centroides_ancien[][nbre_param] : Tableau 2D, contenant par ligne les anciennes valeurs des centroides
- coordonnees_centroides_nouveau[][nbre_param]: TYableau 2D, contenant par ligne les nouvelles valeurs de centroides
- K : Nombre de centroides
- distance_centroide_centroide[]: Tableau contenant dans l'ordre, les distances de chaque centroide par rapport à son ancienne valeur*/

void distance_entre_centroides(double coordonnees_centroides_ancien[][nbre_param], double coordonnees_centroides_nouveau[][nbre_param], int K, double distance_centroide_centroide[]);

/*Fonction qui détermine si toutes les valeurs d'un tableau sont inférieures ou égales à une valeur donnée
- tableau[] : Tableau de réels
- taille : entier -> taille du tableau
- valeur : réel auquel sont comparées les valeurs du tableau*/

int sont_inf (double tableau[], int taille, double valeur);

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
void k_means (double jeu_de_donnees[][nbre_param], int nbre_patients, double coordonnees_centroides[][nbre_param],  int indice_membres_clusters [][NBMAX_membres_cluster], int nombre_elements_cluster [], int K, int Nbre_iterations, double seuil);

#endif /* KMEANS_UTILITAIRES_H */