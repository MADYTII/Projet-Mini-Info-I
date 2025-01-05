#include <stdio.h>
#include "extraction_donnees.h"
#include "perceptron_utilitaires.h"

/*Fonction activation retourne 1 si le modéle linéaire évalué sur des données individuelles est >=0 et 0 sinon*/
// poids_bais[] :  tableau de réels contenant dans l'ordre les poids w1, w2, ...., wn et le biais b
// caract_values[] = tableau de réels  contenant les valeurs des caractéristques x1, x2,...,xn et 1 comme entrée fictive associée au biais b 
// taille_commune = longueur des tableaus poids_biais et caract_values
int activation (double poids_biais[], double caract_values[], int taille_commune){ 
    //l'évaluation du modèle linéaire (w1 * x1 + w2 * x2 + .... + wn * xn + b)  revient à faire un produit scalaire entre les tableaus poids_biais et caract_values
    double produit_scalaire = 0.; 
    for(int i = 0; i < taille_commune; i++){ 
        produit_scalaire += poids_biais[i] * caract_values[i];  
    }
    //Génération du résultat de la fonction d'activation
    if (produit_scalaire >= 0){ 
        return 1.;
    }
    else{
        return 0.;
    }
} 


//Correction des poids et du biais lorsqu'un patient est mal classé par le modèle
// poids_bais[] :  tableau de réels contenant dans l'ordre les poids w1, w2, ...., wn et le biais b
// caract_values[] = tableau de réels  contenant les valeurs des caractéristques x1, x2,...,xn et 1 comme entrée fictive associée au biais b
// taille_commune = longueur des tableaux poids_biais et caract_values
// taux_apprentissage: taux d'apprentissage,
// risque_predit: etat de risque predit  
// risque_attendu : etat de risque attendu
void ajustement_poids(double poids_biais[], double caract_values[], int taille_commune, double taux_apprentissage, double risque_predit, double risque_attendu){
    for (int i = 0; i < taille_commune; i++){
        poids_biais[i] += taux_apprentissage * (risque_attendu - risque_predit) * caract_values[i];
    }
}


// Algorithme de classification du perceptron (test) : renvoie le taux d'erreur de classification du modèle sur un jeu de données lp
// lp : liste de patients à classer + leurs caractéristiques
// nombre_patients : Nombre de patients dans la liste
// liste_id_caract[] : liste des identifiants de caractéristiques selon lesquelles seront effectuées la classification
// nbre_caract : Nombre de caractéristqiques selon lesquelles s'effectue la classification
// poids_biais[]: tableau contenant les poids w1, ..., Wn et le biais b (en dernière position)

double perceptron_test(liste_patients lp, int nombre_patients, int liste_id_caract[], int nbre_caract, double poids_biais[]){
    int nbre_mal_classe = 0;                                     // initialisation du nombre de patients mal classés
    double caract_values[ nbre_caract + 1];                  // tableau des valeurs des caractéristiques mentionnées dans liste_id_caract  pour un patient de lp
    for(int i = 0; i < nombre_patients; i++){                // Pour chaque patient de lp..
            
        for(int j = 0; j < nbre_caract; j++){                // récupération des valeurs de chaque caractéristique 
            caract_values[j] = extraction_donnees(lp.liste[i], liste_id_caract[j]);
        }
        caract_values[nbre_caract] = 1;     // Entrée fictive associée au biais. 
        double risque_predit = activation(poids_biais, caract_values, nbre_caract + 1);  // Evaluation de la fonction d'activation pour le patient en cours lp.liste[i]
        double risque_attendu = extraction_donnees(lp.liste[i], 9); // récupération de la vraie valeur du risque (risk : id_carac = 9)

        if (risque_attendu != risque_predit){  // Si la valeur prédite est différente de la valeur attendue
            nbre_mal_classe++;                 // Incrémentation du nombre de patients mal classés
        }
        
    } 
    return (double) nbre_mal_classe / (double) nombre_patients; // taux d'erreur sur l'ensemble de test
}

// Algorithme de classification du perceptron (entrainement)
// lp : liste de patients à classer + leurs caractéristiques
// nombre_patients : Nombre de patients dans la liste
// liste_id_caract[] : liste des identifiants de caractéristiques selon lesquelles seront effectuées la classification
// nbre_caract : Nombre de caractéristqiques selon lesquelles se fait la classification
// poids_biais[]: tableau contenant les poids w1, ..., Wn et le biais b (en dernière position)
// taux_apprentissage : taux d'apprentissage du perceptron
//  Nombre_iterations :  Nombre d'itérations maximal en cas de non convergence

void perceptron_entrainement(liste_patients lp, int nombre_patients, int liste_id_caract[], int nbre_caract, double poids_biais[], double taux_apprentissage, int Nombre_iterations){
    int nbre_mal_classe;                                            // variable devant contenir le nombre de patienst mal classé par itérations
    int m = 0;
    do{
        nbre_mal_classe = 0;                                     // initialiosation du nombre de patienst mal classés
        double caract_values[ nbre_caract + 1];                  // tableau des valeurs des caractéristiques mentionnées dans liste_id_caract  pour un patient de lp
        for(int i = 0; i < nombre_patients; i++){                // Pour chaque patient de lp..
            
            for(int j = 0; j < nbre_caract; j++){                // récupération des valeurs de chaque caractéristique 
                caract_values[j] = extraction_donnees(lp.liste[i], liste_id_caract[j]);
            }
            caract_values[nbre_caract] = 1;     // Entrée fictive associée au biais. 
            double risque_predit = activation(poids_biais, caract_values, nbre_caract + 1);  // Evaluation de la fonction d'activation pour le patient en cours lp.liste[i]
            double risque_attendu = extraction_donnees(lp.liste[i], 9); // récupération de la vraie valeur du risque (risk : id_carac = 9)

            if (risque_attendu != risque_predit){  // Si la valeur prédite est différente de la valeur attendue
                nbre_mal_classe++;                 // Incrémentation du nombre de patients mal classés
                ajustement_poids(poids_biais, caract_values, nbre_caract + 1, taux_apprentissage, risque_predit, risque_attendu); // Correction des poids et du biais
            }
        
        } 
        //printf("\t iteration %d , error rate = %lf\n", m, (double)nbre_mal_classe / (double)nombre_patients);  // Affichage du taux d'erreur à chaque itération
        m++;
    } while ( m < Nombre_iterations && nbre_mal_classe != 0); // On arrête l'ajustement des coefficients s'il ya convergence (nombre_mal_classe = 0 ou si l'on a atteint le nombre max d'itérations)
}


/* Fonction qui retourne le nom de la caractéristique en fonction de son ID */
/*Convention id_carac: 1 -> age, 2 -> sex, 3 -> weight, 4 -> blood_pressure, 
    5 -> average_heart_rate, 6 -> blood_sugar, 7 -> cholesterol , 8 -> risk*/ 

const char* nom_caracteristique(int id_carac){
    switch (id_carac) {
        case 1: 
            return "Id";
        case 2: 
            return "Age";
        case 3: 
            return "Sex";
        case 4: 
            return "Weight";
        case 5: 
            return "Blood Pressure";
        case 6: 
            return "Average Heart Rate";
        case 7: 
            return "Blood Sugar";
        case 8: 
            return "Cholesterol";
        case 9: 
            return "Risk";
        default: 
            return "Inconnu";
    }
}