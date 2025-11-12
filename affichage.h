#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "structures.h"
// #include <windows.h> // Pas besoin si on ne centre pas

// Codes couleurs pour Windows
#define COULEUR_RESET 7
#define COULEUR_ROUGE 12
#define COULEUR_VIOLET 13
#define COULEUR_ORANGE 6
#define COULEUR_VERT 10
#define COULEUR_JAUNE 14
#define COULEUR_CYAN 11
#define COULEUR_BLANC 15

// Fonctions utilitaires d'affichage
void changerCouleur(int couleur);
void allerA(int x, int y);
void effacerEcran(void);
// int obtenirLargeurConsole(void); // On enlève

// Affichage du menu et des écrans
void afficherMenuPrincipal(void);
void afficherRegles(void);

// Affichage du jeu
void afficherNiveauJeu(Partie* partie, int curseurX, int curseurY, int selectX, int selectY);
void afficherPlateau(Partie* partie, int curseurX, int curseurY, int selectX, int selectY);
void afficherStats(Partie* partie);
void afficherControles(void);
void afficherLegende(void);

// Messages
void afficherVictoire(void);
void afficherDefaite(void);
void afficherMessageTemporaire(char* message);

#endif // AFFICHAGE_H
