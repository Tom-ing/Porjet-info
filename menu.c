#include <stdio.h>
#include "menu.h"
#include "affichage.h"

// === AFFICHAGE DES MENUS ===
void afficherMenuPrincipal(void) {
    effacerEcran();

    changerCouleur(COULEUR_VERT);
    printf("\n");
    printf("    ╔══════════════════════════════════════════════════════════╗\n");
    printf("    ║                                                          ║\n");
    printf("    ║               ████████  ███████ ████████                 ║\n");
    printf("    ║               ██       ██       ██                       ║\n");
    printf("    ║               ███████  ██       ███████                  ║\n");
    printf("    ║               ██       ██       ██                       ║\n");
    printf("    ║               ████████  ███████ ████████                 ║\n");
    printf("    ║                                                          ║\n");
    printf("    ║                       H E R O E S                        ║\n");
    printf("    ║                                                          ║\n");
    printf("    ╚══════════════════════════════════════════════════════════╝\n\n");

    changerCouleur(COULEUR_BLANC);
    printf("    ┌──────────────────────────────────────────────────────────┐\n");
    printf("    │                      MENU PRINCIPAL                      │\n");
    printf("    └──────────────────────────────────────────────────────────┘\n\n");

    changerCouleur(COULEUR_JAUNE); printf("        1. ");
    changerCouleur(COULEUR_BLANC); printf("Lire les règles du jeu\n\n");
    changerCouleur(COULEUR_JAUNE); printf("        2. ");
    changerCouleur(COULEUR_BLANC); printf("Commencer une nouvelle partie\n\n");
    changerCouleur(COULEUR_JAUNE); printf("        3. ");
    changerCouleur(COULEUR_BLANC); printf("Reprendre une partie sauvegardée\n\n");
    changerCouleur(COULEUR_JAUNE); printf("        4. ");
    changerCouleur(COULEUR_BLANC); printf("Quitter\n\n");
    changerCouleur(COULEUR_CYAN);  printf("    >> Votre choix : ");
    changerCouleur(COULEUR_RESET);
}
