# README

## Introduction

Ce projet est une implémentation d'un perceptron pour la classification de patients en fonction de diverses caractéristiques médicales. Il inclut des outils pour l'extraction de données, leur normalisation, et la gestion des structures de patients. Il s'agit d'un projet académique visant à démontrer une maîtrise des concepts algorithmiques et de programmation structurée.

## Structure du projet

### `patients.pengu`

- Ce fichier contient les données brutes des patients utilisées comme entrée pour les algorithmes. Chaque ligne représente un patient et inclut ses caractéristiques, telles que l'âge, le sexe, le poids, la pression artérielle, la glycémie, le cholestérol et un indicateur de risque ("True" ou "False").
- Le programme utilise ces données pour l'entraînement et le test du perceptron, garantissant ainsi une évaluation précise des performances du modèle.

Tous les fichiers sont organisés dans des dossiers spécifiques :

- **`perceptron_include/`** : Contient les fichiers `.h` nécessaires pour définir les structures et déclarer les fonctions utilisées dans le projet.
- **`perceptron_src/`** : Contient les fichiers `.c` implémentant les fonctions décrites dans les fichiers `.h`.
- **`perceptron_data/`** : Contient le fichier `patients.pengu`, qui regroupe les données des patients utilisées comme entrée pour les algorithmes.

Voici un aperçu des fichiers principaux du projet:

- **`types_struct.h`** :

  - Définit les structures principales utilisées dans le projet :
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
      - Génère des statistiques précises sur l'efficacité du modèle pour des ensembles de données inconnues.

- **`main_perceptron.c`** :

  - Le point d'entrée du programme :
    - Charge les données des patients.
    - Divise les données en ensembles d'entraînement et de test.
    - Normalise les données pour s'assurer qu'elles sont prêtes pour le traitement par le perceptron.
    - Entraîne et teste le perceptron sur différents ensembles de caractéristiques, affichant les résultats.

## Compilation

Pour compiler le projet, suivez ces étapes :

1. Téléchargez et extrayez le dossier du programme (s'il est fourni sous forme d'archive).
2. Définissez le dossier extrait comme répertoire courant avec la commande `cd` :
   ```bash
   cd chemin/vers/le/dossier
   ```
3. Utilisez le `Makefile` fourni. Les commandes suivantes sont disponibles :

- `make` : Exécute la commande `all` par défaut, qui compile les fichiers, génère l'exécutable, exécute le programme principal et nettoie les fichiers temporaires.
- `make run` : Compile le projet et exécute automatiquement l'exécutable principal.
- `make clean` : Supprime les fichiers intermédiaires et l'exécutable pour nettoyer le répertoire.
- `make all` : Effectue la compilation, exécute le programme principal, puis nettoie automatiquement les fichiers temporaires.

**Exemple d'utilisation :**

```bash
make
# La commande 'make' exécute 'all', qui compile, exécute et nettoie automatiquement le projet.
```

## Exécution

Une fois le projet compilé, le programme principal est exécuté automatiquement par la commande `make` (qui exécute la cible `all`). Cela inclut la compilation, l'exécution du programme principal et le nettoyage des fichiers temporaires, conformément au fonctionnement décrit dans le `Makefile`.

Le programme chargera automatiquement les données des patients à partir du fichier `patients.pengu` et appliquera les algorithmes du perceptron pour la classification et l'évaluation des risques. à partir du fichier `patients.pengu` et appliquera les algorithmes du perceptron pour la classification et l'évaluation des risques.

## Fonctionnalités

- **Lecture des données** : Lecture des patients depuis un fichier texte structurant.
- **Extraction de données** : Accès rapide à des caractéristiques individuelles ou des statistiques.
- **Normalisation des données** : Calcul des min/max et standardisation des valeurs pour les algorithmes de classification.
- **Classification avec perceptron** : Algorithmes d'entraînement et de test pour classer les patients en fonction de leurs risques.

## Exemple d'utilisation

Pour effectuer une classification des patients :

1. Charger les données :

   ```c
   liste_patients lp;
   charger_fichier(&lp, "patients.pengu", nbre_patients);
   ```

2. Normaliser les données :

   ```c
   normalisation(&lp, nbre_patients, liste_id_caract, nbre_caract, tableau_min, tableau_max);
   ```

3. Entraîner le perceptron :

   ```c
   perceptron_entrainement(lp, nbre_patients, liste_id_caract, nbre_caract, poids_biais, taux_apprentissage, nb_iterations);
   ```

4. Tester le modèle :

   ```c
   double taux_erreur = perceptron_test(lp, nbre_patients, liste_id_caract, nbre_caract, poids_biais);
   ```

## Licence

Ce projet est libre de droits. Utilisez-le et modifiez-le selon vos besoins.

