#ifndef STRUCTURES_H
#define STRUCTURES_H

// --- DIMENSIONS DU JEU ---
// On définit la taille de la grille (20 lignes, 15 colonnes)
#define HAUTEUR 20
#define LARGEUR 15

// --- IDENTIFIANTS DES OBJETS ---
// Les fruits vont de 1 à 5.
#define NB_TYPES_ITEMS 5
#define ITEM_BOMBE 6    // Bonus qui explose
#define ITEM_MUR 7     // Obstacle immobile
#define ITEM_VIRUS 8

// --- PARAMÈTRES GLOBAUX ---
#define NB_VIES_INITIAL 3
#define NB_NIVEAUX 3

// === STRUCTURE PRINCIPALE ===
// Rôle : C'est la "boîte" qui contient toutes les infos de la partie en cours.
// On la passe en paramètre à presque toutes les fonctions pour qu'elles sachent quoi modifier.
typedef struct {
    int tableau[HAUTEUR][LARGEUR]; // La grille de jeu (contient les ID des fruits)
    int vies;                      // Nombre de vies du joueur
    int niveau;                    // Niveau actuel (1, 2 ou 3)
    int coups_restants;            // Compteur de mouvements (Défaite si 0)
    int temps_restant;             // Compteur de temps en secondes (Défaite si 0)

    // Gestion des objectifs
    int contrat[NB_TYPES_ITEMS];   // Combien de fruits il faut collecter (Objectif)
    int elimines[NB_TYPES_ITEMS];  // Combien on en a déjà collecté (Progression)
} Partie;

#endif // STRUCTURES_H
