/*
* ════════════════════════════════════════════════════════════════════════════
 * FICHIER: structures.h
 * Description: Définition des structures de données
 * ════════════════════════════════════════════════════════════════════════════
 */

#ifndef STRUCTURES_H
#define STRUCTURES_H

#define HAUTEUR 25
#define LARGEUR 45
#define NB_TYPES_ITEMS 5
#define NB_VIES_INITIAL 3
#define NB_NIVEAUX 3

// Structure représentant une partie
typedef struct {
    int tableau[HAUTEUR][LARGEUR];  // 0=vide, 1-5=types d'items
    int vies;
    int niveau;
    int coups_restants;
    int temps_restant;  // en secondes
    int contrat[NB_TYPES_ITEMS];  // Objectifs par type d'item
    int elimines[NB_TYPES_ITEMS]; // Items éliminés par type
} Partie;

// Structure pour sauvegarder une partie
typedef struct {
    char pseudo[50];
    int dernier_niveau;
    int vies_restantes;
} Sauvegarde;

#endif // STRUCTURES_H
