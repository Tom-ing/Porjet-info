#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "moteur.h"

// Initialise une nouvelle partie
void initialiserPartie(Partie* partie) {
    partie->niveau = 1;
    partie->vies = NB_VIES_INITIAL;
    genererNiveau(partie, 1);
}

// Génère un niveau
void genererNiveau(Partie* partie, int niveau) {
    partie->niveau = niveau;
    partie->coups_restants = 30;
    partie->temps_restant = 120;

    // Initialiser le contrat
    for (int i = 0; i < NB_TYPES_ITEMS; i++) {
        partie->contrat[i] = 10 + (niveau * 5);// par exemple au niveau 1 seulement 15 items par types d'items est
                                                 //demandé pour remplir le contrat
        partie->elimines[i] = 0;//on s'assure que le joureur commence  avec 0 items éliminé
    }

    remplirTableauAleatoire(partie->tableau);
}

// Remplit le tableau aléatoirement
void remplirTableauAleatoire(int tableau[HAUTEUR][LARGEUR]) {
    srand(time(NULL));

    for (int i = 0; i < HAUTEUR; i++) {
        for (int j = 0; j < LARGEUR; j++) {
            tableau[i][j] = (rand() % NB_TYPES_ITEMS) + 1;
        }
    }
}

// Vérifie si deux cases sont adjacentes
int estAdjacent(int y1, int x1, int y2, int x2) {
    if (abs(y1 - y2) + abs(x1 - x2) == 1) {
        return 1;
    }
    return 0;
}

// Permute deux items dans le tableau
// Retourne 1 si la permutation a lieu, 0 sinon
int permuterItems(Partie* partie, int y1, int x1, int y2, int x2) {
    if (!estAdjacent(y1, x1, y2, x2)) {
        return 0; // Ne permute pas si il ne sont pas à coté
    }

    // Logique de permutation
    int temp = partie->tableau[y1][x1];
    partie->tableau[y1][x1] = partie->tableau[y2][x2];
    partie->tableau[y2][x2] = temp;

    // Décrémente les coups
    partie->coups_restants--;

    return 1;
}

void appliquerGravite(Partie* partie) {
    // Boucle pour chaque colonne
    for (int j = 0; j < LARGEUR; j++) {
        // 'k' est notre "pointeur d'écriture"
        // Il commence en bas et remonte
        int k = HAUTEUR - 1;

        // On lit la colonne de bas en haut
        for (int i = HAUTEUR - 1; i >= 0; i--) {
            // Si on trouve un item non-vide
            if (partie->tableau[i][j] != 0) {
                // On le déplace vers le bas à la position 'k'
                partie->tableau[k][j] = partie->tableau[i][j];

                // Si 'i' et 'k' ne sont pas au même endroit,
                // on vide la case d'origine
                if (i != k) {
                    partie->tableau[i][j] = 0;
                }
                // On déplace le pointeur d'écriture vers le haut
                k--;
            }
        }

        // Toutes les cases au-dessus de 'k' sont maintenant vides (0)
        // (La boucle 'i' s'est assurée de ça)
    }
}

void remplirCasesVides(Partie* partie) {
    for (int i = 0; i < HAUTEUR; i++) {
        for (int j = 0; j < LARGEUR; j++) {
            if (partie->tableau[i][j] == 0) {
                partie->tableau[i][j] = (rand() % NB_TYPES_ITEMS) + 1;
            }
        }
    }
}

int detecterEtEliminerMatchs(Partie* partie) {
    int totalElimines = 0;
    // Tableau temporaire pour marquer les items à supprimer
    int marques[HAUTEUR][LARGEUR] = {0};

    // --- 1. Détection des figures ---

    for (int i = 0; i < HAUTEUR; i++) {
        for (int j = 0; j < LARGEUR; j++) {
            int item = partie->tableau[i][j];
            if (item == 0) continue; // Case vide


            // --- Règle 1 : Suite de 6 (Horizontale) ---
            // Effet : Élimine TOUS les items de ce type sur le plateau
            if (j <= LARGEUR - 6 &&
                partie->tableau[i][j+1] == item &&
                partie->tableau[i][j+2] == item &&
                partie->tableau[i][j+3] == item &&
                partie->tableau[i][j+4] == item &&
                partie->tableau[i][j+5] == item)
            {
                for (int y = 0; y < HAUTEUR; y++) {
                    for (int x = 0; x < LARGEUR; x++) {
                        if (partie->tableau[y][x] == item) {
                            marques[y][x] = 1;
                        }
                    }
                }
            }

            // --- Règle 1 : Suite de 6 (Verticale) ---
            // Effet : Élimine TOUS les items de ce type sur le plateau
            if (i <= HAUTEUR - 6 &&
                partie->tableau[i+1][j] == item &&
                partie->tableau[i+2][j] == item &&
                partie->tableau[i+3][j] == item &&
                partie->tableau[i+4][j] == item &&
                partie->tableau[i+5][j] == item)
            {
                for (int y = 0; y < HAUTEUR; y++) {
                    for (int x = 0; x < LARGEUR; x++) {
                        if (partie->tableau[y][x] == item) {
                            marques[y][x] = 1;
                        }
                    }
                }
            }

            // --- NOUVELLE RÈGLE 2 : Croix (5x5) ---
            // Forme : Une ligne de 5H et 5V qui se croisent
            // Effet : Élimine tous les items de ce type sur la LIGNE et la COLONNE
            if (i >= 2 && i < HAUTEUR - 2 && j >= 2 && j < LARGEUR - 2 &&
                // Ligne Horizontale de 5
                partie->tableau[i][j-1] == item && partie->tableau[i][j-2] == item &&
                partie->tableau[i][j+1] == item && partie->tableau[i][j+2] == item &&
                // Ligne Verticale de 5
                partie->tableau[i-1][j] == item && partie->tableau[i-2][j] == item &&
                partie->tableau[i+1][j] == item && partie->tableau[i+2][j] == item)
            {
                // Marque toute la LIGNE (i)
                for (int x = 0; x < LARGEUR; x++) {
                    if (partie->tableau[i][x] == item) {
                        marques[i][x] = 1;
                    }
                }
                // Marque toute la COLONNE (j)
                for (int y = 0; y < HAUTEUR; y++) {
                    if (partie->tableau[y][j] == item) {
                        marques[y][j] = 1;
                    }
                }
            }

            // --- NOUVELLE RÈGLE 3 : Carré (4x4) ---
            // Effet : Élimine tous les items de ce type DANS le carré
            if (i <= HAUTEUR - 4 && j <= LARGEUR - 4) {
                int estCarre = 1;
                // Vérifie les 16 cases
                for (int y = i; y < i + 4; y++) {
                    for (int x = j; x < j + 4; x++) {
                        if (partie->tableau[y][x] != item) {
                            estCarre = 0;
                            break;
                        }
                    }
                    if (!estCarre) break;
                }

                if (estCarre) {
                    // Marque les 16 cases du carré
                    for (int y = i; y < i + 4; y++) {
                        for (int x = j; x < j + 4; x++) {
                            marques[y][x] = 1;
                        }
                    }
                }
            }

            // --- Règle 4 : Suite de 4 (Horizontale) ---
            // Effet : Élimine les 4 items
            if (j <= LARGEUR - 4 &&
                partie->tableau[i][j+1] == item &&
                partie->tableau[i][j+2] == item &&
                partie->tableau[i][j+3] == item)
            {
                marques[i][j] = 1; marques[i][j+1] = 1;
                marques[i][j+2] = 1; marques[i][j+3] = 1;
            }

            // --- Règle 4 : Suite de 4 (Verticale) ---
            // Effet : Élimine les 4 items
            if (i <= HAUTEUR - 4 &&
                partie->tableau[i+1][j] == item &&
                partie->tableau[i+2][j] == item &&
                partie->tableau[i+3][j] == item)
            {
                marques[i][j] = 1; marques[i+1][j] = 1;
                marques[i+2][j] = 1; marques[i+3][j] = 1;
            }
        }
    }

    // --- 2. Élimination et Score ---

    for (int i = 0; i < HAUTEUR; i++) {
        for (int j = 0; j < LARGEUR; j++) {
            if (marques[i][j] == 1) {
                int itemType = partie->tableau[i][j];

                // Met à jour le contrat (score)
                if (itemType >= 1 && itemType <= NB_TYPES_ITEMS) {
                    int index = itemType - 1;
                    // On n'augmente le score QUE si le contrat n'est pas déjà rempli
                    if (partie->elimines[index] < partie->contrat[index]) {
                        partie->elimines[index]++;
                    }
                }

                // Élimine l'item du plateau
                partie->tableau[i][j] = 0;
                totalElimines++;
            }
        }
    }

    return totalElimines;
}

void gererMatchsEtCascades(Partie* partie) {
    // Boucle "Jusqu'à stabilisation"
    while (detecterEtEliminerMatchs(partie) > 0) {
        appliquerGravite(partie);// Appliquer la gravité
        remplirCasesVides(partie);// Remplir les cases vides
    }
}

int verifierVictoire(Partie* partie) {
    for (int i = 0; i < NB_TYPES_ITEMS; i++) {
        // Si un seul objectif n'est pas atteint...
        if (partie->elimines[i] < partie->contrat[i]) {
            return 0; // Défaite
        }
    }
    // Si la boucle se termine, c'est que tout est atteint.
    return 1; // Victoire
}
