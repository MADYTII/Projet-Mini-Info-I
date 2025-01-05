# README

## Introduction

Ce projet est une implémentation d'une part d'un algorithme d'apprentissage supervisé **`perceptron`**  pour la prédiction de l'étét de risque à une maladie de patients en fonction de données cliniques, et d'autre part d'un algorithme de classification non-supervisé  **`k-means`** pour l'étude de l'existence d'une corrélation entre l'état de risque des patients et des caractéristiques définissant leur style de vie.

## Partie 1. Perceptron

### 1.1) Structure
Tous les fichiers sont organisés dans un grand dossier **`perceptron/`** qui comprends les sous-dossiers spécifiques :

- **`perceptron_include/`** : Contient les fichiers `.h` nécessaires pour définir les structures et déclarer les fonctions utilisées dans le projet.
- **`perceptron_src/`** : Contient les fichiers `.c` implémentant les fonctions décrites dans les fichiers `.h`.
- **`perceptron_data/`** : Contient le fichier `patients.pengu`, qui regroupe les données des patients utilisées comme entrée pour les algorithmes.

Voici un aperçu des fichiers principaux de cette implémentation de perceptron:

- **`types_struct.h`** :

  - Définit les structures principales utilisées dans cette partie :
    - `patient` : représente les informations individuelles d'un patient, comprenant des attributs tels que l'âge, le sexe, le poids, la pression artérielle, la glycémie, le cholestérol et un indicateur de risque ("True" ou "False").
    - `liste_patients` : regroupe une collection de patients pour permettre leur traitement en masse.

- **`echantillonnage.h`**** et ****`echantillonnage.c`** :

  - Fournit des fonctions pour gérer l'échantillonnage et la division des données :
    - **`melanger_tableau_FYK`** : Implémente l'algorithme de Fisher-Yates pour mélanger un tableau d'entiers de manière aléatoire, garantissant une distribution équitable des données tout en maintenant la reproductibilité grâce à une graine fixe. Cet algorithme est appliqué aux identifiants des patients afin d'assurer une répartition aléatoire entre les sous-ensembles d'entraînement et de test.
    - **`repartition_valeurs`** : Divise un tableau d'identifiants en deux sous-ensembles (par exemple, ensemble d'entraînement et ensemble de test) en respectant les proportions spécifiées. Les sous-ensembles ainsi générés servent respectivement à entraîner le modèle et à évaluer sa performance.
    - **`remplir_liste_patients`** : Copie les données des patients désignés par leurs identifiants dans une nouvelle structure `liste_patients`, ce qui est crucial pour isoler des sous-ensembles de données.

- **`extraction_donnees.h`**** et ****`extraction_donnees.c`** :

  - Fournit des outils pour accéder rapidement aux données des patients :
    - **`extraction_donnees`** : Récupère une caractéristique spécifique d'un patient en fonction de son identifiant (par exemple, 2 pour l'âge, 8 pour le cholestérol).
    - **`conversion_sex`** et **`conversion_risk`** : Convertissent respectivement le sexe et l'indicateur de risque en valeurs numériques pour les calculs.

- **`lecture_fichier.h`**** et ****`lecture_fichier.c`** :

  - Gère la lecture des fichiers de données :
    - **`longueur_fichier`** : Compte le nombre de lignes dans un fichier pour déterminer combien de patients sont inclus dans les données.
    - **`charger_fichier`** : Lit un fichier texte formaté (`patients.pengu`), extrait les données des patients ligne par ligne, et remplit une structure `liste_patients`.

- **`normalisation.h`**** et ****`normalisation.c`** :

  - Contient des fonctions pour préparer les données avant leur utilisation dans le perceptron :
    - **`minimum`** et **`maximum`** :
      - `minimum` calcule la plus petite valeur pour chaque caractéristique spécifiée dans une liste d'identifiants, en parcourant tous les patients d'un ensemble.
      - `maximum` calcule de manière similaire la valeur maximale. Ces fonctions sont essentielles pour déterminer les bornes nécessaires à la normalisation.
    - **`normalisation`** :
      - Applique une transformation linéaire pour standardiser les caractéristiques des patients. La normalisation suit la formule :

        Valeur normalisée = (Valeur - Min) / (Max - Min)

        Cette transformation garantit que les valeurs de chaque caractéristique sont redimensionnées dans un intervalle . Les caractéristiques booléennes ou catégoriques ne sont pas concernées par cette opération. Le processus s'effectue en deux étapes :

        1. Les valeurs des caractéristiques de l'ensemble d'entraînement sont normalisées en fonction de leurs bornes (min et max).
        2. Les mêmes bornes (min et max) sont utilisées pour normaliser les valeurs de l'ensemble de test, assurant ainsi une cohérence entre les ensembles.

      - La normalisation est cruciale pour éviter que des caractéristiques ayant des plages de valeurs très différentes n'influencent de manière disproportionnée l'entraînement du modèle de perceptron.

- **`perceptron_utilitaires.h`**** et ****`perceptron_utilitaires.c`** :

  - Implémente l'algorithme du perceptron, un modèle de classification binaire :
    - **`activation`** :
      - Calcule la sortie du modèle (1 ou 0) en effectuant le produit scalaire entre les poids (y compris le biais) et les valeurs des caractéristiques d'un patient.
      - Permet de déterminer si un patient est classé comme à risque ou non en fonction de la sortie.
    - **`ajustement_poids`** :
      - Corrige les poids du perceptron pour réduire les erreurs de classification en ajustant chaque poids proportionnellement à l'erreur (différence entre la valeur prédite et la valeur attendue).
      - Garantit que le modèle apprend de ses erreurs et s'améliore au fil des itérations.
    - **`perceptron_entrainement`** :
      - Entraîne le perceptron sur un ensemble d'entraînement en effectuant plusieurs itérations pour minimiser les erreurs de classification.
      - Arrête l'entraînement lorsqu'il n'y a plus d'erreurs ou qu'un nombre maximal d'itérations est atteint.
      - Utilise l'algorithme d'ajustement des poids pour optimiser les coefficients du modèle.
    - **`perceptron_test`** :
      - Évalue les performances du perceptron sur un ensemble de test en calculant le taux d'erreur, défini comme le ratio entre le nombre de patients mal classés et le nombre total de patients.

- **`main_perceptron.c`** :

  - Le point d'entrée du programme :
    - Charge les données des patients.
    - Divise les données en ensembles d'entraînement et de test.
    - Normalise les données pour s'assurer qu'elles sont prêtes pour le traitement par le perceptron.
    - Entraîne et teste le perceptron sur différents ensembles de caractéristiques, affichant les résultats.

## 1.2) Fonctionnalités

- **Lecture des données** : Lecture des patients depuis un fichier texte structurant.
- **Extraction de données** : Accès rapide à des caractéristiques individuelles ou des statistiques.
- **Normalisation des données** : Calcul des min/max et standardisation des valeurs pour les algorithmes de classification.
- **Classification avec perceptron** : Algorithmes d'entraînement et de test pour classer les patients en fonction de leurs risques.

## Partie 2. Kmeans


### 2.1) Structure

Tous les fichiers sont organisés dans un grand dossier kmeans qui comprends les sous-dossiers suivants:
- **`kmeans_include/`** : Contient les fichiers `.h` nécessaires pour définir les structures et déclarer les fonctions utilisées dans le projet.
- **`kmeans_src/`** : Contient les fichiers `.c` implémentant les fonctions décrites dans les fichiers `.h`.
- **`kmeans_data/`** : Contient les fichier `patients.pengu` et "lifestyle.pengu", qui regroupent respctivement les données dur l'état de risque et les styles de vie des patients exploitées pour cette analyse.

Ci-dessous, un aperçu des fichiers principaux de cette implémentation de kmeans:

**`constantes.h`** :

- Définit les constantes globales utilisées dans le projet :

  - `NBMAX_patients` : Le nombre maximum de patients supporté (8000).
  - `NBMAX_membres_cluster` : Le nombre maximum de patients par cluster (5000).
  - `nbre_param` : La dimension de l'espace de classification, correspondant au nombre de paramètres de style de vie (4).

- **`types_struct.h`** :

  - Définit les structures principales utilisées dans le projet :
    - `patient` : représente les informations individuelles d'un patient, comprenant des attributs tels que l'activité physique, la consommation d'alcool, et la qualité du sommeil.
    - `liste_patients` : regroupe une collection de patients pour permettre leur traitement en masse.

- **`file_handling.h`**\*\* et \*\***`file_handling.c`** :

  - Fournit des fonctions pour la gestion des fichiers :
    - `longueur_fichier` : Compte le nombre de lignes dans un fichier afin de déduire le nombre de patients.
    - `charger_lifestyle` : Charge les caractéristiques de style de vie des patients depuis un fichier "lifestyle.pengu".
    - `charger_risk` : Associe les informations sur l'état de risque des patients par lecture du fichier "patients.pengu".

- **`normalisation.h`**\*\* et \*\***`normalisation.c`** :

  - Contiennent des fonctions pour préparer les données avant leur utilisation dans l'algorithme K-means :
    - `minimum_lp` et `maximum_lp` : Calculent respectivement les valeurs minimales et maximales de chacun des paramètres de style de vie.
    - `normalisation` : Standardise les paramètres de style de vie des patients à l'aide des bornes min et max calculées précdemment.
    - `denormaliser_centroides` : Restaure les coordonnées des centroides à leur échelle d'origine pour faciliter les analyses.

- **`kmeans_utilitaires.h`**\*\* et \*\***`kmeans_utilitaires.c`** :

  - Implémentent  l'algorithme K-means et des fonctions auxiliaires :
    - `entier_aléatoire` : permet la sélection aléatoire de patients qui représenteront des centroides initiaux.
    - `distance_euclidienne` : Calcule la distance entre deux points (patients) de l'espace de classification.
    - `nouveaux_centroides` : Calcule les nouveaux centroides pour chaque cluster.
    - `k_means` : Implémente l’algorithme K-means (calcul de distances aux centroides pour chaque patient, assignation d'un patient à un cluster, recalcul de nouveaux centroides jusqu'à ce que la convergence où le nombre maximum d'itérations imposé soit atteint).

- **`analyse_cluster.h`**\*\* et \*\***`analyse_cluster.c`** :

  - Fournit des outils pour analyser les clusters formés :
    - `decompte_true_false` : Compte les patients à risque "True" et ceux à risque "False" dans chaque cluster.
    - `etat_risque_cluster` : Évalue l'homogénéité des clusters en termes de risques associés.

- **`main_kmeans.c`** :

  - Le point d'entrée du programme :
    - Charge les données des patients.
    - Normalise les données pour s'assurer qu'elles sont prêtes pour le traitement par l'algorithme K-means.
    - Applique l'algorithme et affiche les résultats d'analyse des clusters.

## 2.2) Fonctionnalités

- **Lecture des données** : Lecture des caractéristiques des patients depuis un fichier texte structuré.
- **Normalisation des données** : Calcul des min/max et standardisation des valeurs pour une meilleure convergence.
- **Classification avec K-means** : Algorithme d'entraînement pour regrouper les patients en clusters homogènes.
- **Analyse des clusters** : Exploration des clusters pour identifier leur homogénéité et leur corrélation avec les risques.


## Partie 3. Compilation

Pour compiler le projet, suivez ces étapes :

1. Télécharger le dépôt complet "Projet_Mini_Info_I" et effectuer une extraction à partir du fichier zip obtenu.
2. Définissez ensuite, à l'intérieur du dossier extrait, soit le dossier **`perceptron/`** soit  celui **`kmeans/`** comme répertoire courant à l'aide de la commande `cd` :
   ```bash
   cd chemin/vers/le/dossier/extrait/kmeans
   ou
   cd chemin/vers/le/dossier/extrait/perceptron
   ```
3. Utilisez le `Makefile` fourni. Les commandes suivantes sont disponibles :

- `make` : Exécute la commande `all` par défaut, qui compile les fichiers, génère l'exécutable, exécute le programme principal (grâce à la commande run) et nettoie les fichiers temporaires (clean).
- `make run` : Compile le projet et exécute automatiquement l'exécutable principal.
- `make clean` : Supprime les fichiers intermédiaires et l'exécutable pour nettoyer le répertoire.

**Exemple d'utilisation :**
Le répertoire courant ayant été défini dans le dossier issu de l'extraction consuite à partir du fichier.zip
Tapez la commande ci-dessous : 
```bash
make
# La commande 'make' exécute 'all', qui compile, exécute et nettoie automatiquement les fichiers temporaires.
```



