#ifndef PERCEPTRON_UTILITAIRES_H
#define PERCEPTRON_UTILITAIRES_H
#include "types_struct.h"

/*Fonction activation retourne 1 si le modéle linéaire évalué sur des données individuelles est >=0 et 0 sinon*/
// poids_bais[] :  tableau de réels contenant dans l'ordre les poids w1, w2, ...., wn et le biais b
// caract_values[] = tableau de réels  contenant les valeurs des caractéristques x1, x2,...,xn et 1 comme entrée fictive associée au biais b 
// taille_commune = longueur des tableaus poids_biais et caract_values
int activation (double poids_biais[], double caract_values[], int taille_commune);


//Correction des poids et du biais lorsqu'un patient est mal classé par le modèle
// poids_bais[] :  tableau de réels contenant dans l'ordre les poids w1, w2, ...., wn et le biais b
// caract_values[] = tableau de réels  contenant les valeurs des caractéristques x1, x2,...,xn et 1 comme entrée fictive associée au biais b
// taille_commune = longueur des tableaux poids_biais et caract_values
// taux_apprentissage: taux d'apprentissage,
// risque_predit: etat de risque predit  
// risque_attendu : etat de risque attendu
void ajustement_poids(double poids_biais[], double caract_values[], int taille_commune, double taux_apprentissage, double risque_predit, double risque_attendu);



// Algorithme de classification du perceptron (test) : renvoie le taux d'erreur de classification du modèle sur un jeu de données lp
// lp : liste de patients à classer + leurs caractéristiques
// nombre_patients : Nombre de patients dans la liste
// liste_id_caract[] : liste des identifiants de caractéristiques selon lesquelles seront effectuées la classification
// nbre_caract : Nombre de caractéristqiques selon lesquelles s'effectue la classification
// poids_biais[]: tableau contenant les poids w1, ..., Wn et le biais b (en dernière position)

double perceptron_test(liste_patients lp, int nombre_patients, int liste_id_caract[], int nbre_caract, double poids_biais[]);



// Algorithme de classification du perceptron (entrainement)
// lp : liste de patients à classer + leurs caractéristiques
// nombre_patients : Nombre de patients dans la liste
// liste_id_caract[] : liste des identifiants de caractéristiques selon lesquelles seront effectuées la classification
// nbre_caract : Nombre de caractéristqiques selon lesquelles se fait la classification
// poids_biais[]: tableau contenant les poids w1, ..., Wn et le biais b (en dernière position)
// taux_apprentissage : taux d'apprentissage du perceptron
//  Nombre_iterations :  Nombre d'itérations maximal en cas de non convergence

void perceptron_entrainement(liste_patients lp, int nombre_patients, int liste_id_caract[], int nbre_caract, double poids_biais[], double taux_apprentissage, int Nombre_iterations);


/* Fonction qui retourne le nom de la caractéristique en fonction de son ID */
/*Convention id_carac: 1 -> age, 2 -> sex, 3 -> weight, 4 -> blood_pressure, 
    5 -> average_heart_rate, 6 -> blood_sugar, 7 -> cholesterol , 8 -> risk*/ 

const char* nom_caracteristique(int id_carac);

#endif /*PERCEPTRON_UTILITAIRES_H*/