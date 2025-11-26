#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "structures.h"

// Codes couleurs pour utiliser les couleurs de Windowq
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

// Affichage du menu et des écrans
void afficherMenuPrincipal(void);
void afficherRegles(void);

// Affichage du jeu
void afficherNiveauJeu(Partie* partie, int curseurX, int curseurY, int selectX, int selectY);

// Ces fonctions prennent maintenant des coordonnées
void afficherPlateau(Partie* partie, int curseurX, int curseurY, int selectX, int selectY, int startX, int startY);
void afficherStats(Partie* partie, int startX, int startY);
void afficherControles(int startX, int startY);
void afficherLegende(int startX, int startY);

//Source: Chatgpt pour la rafraichissement unique du Timer car sinon injouable
void rafraichirTimerSeulement(Partie* partie);

// Messages
void afficherVictoire(void);
void afficherEcranFinJeu(void);
void afficherDefaite(void);
void afficherMessageTemporaire(char* message);

#endif // AFFICHAGE_H
