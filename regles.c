#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "regles.h"
#include "affichage.h"

// === AFFICHAGE DES RÈGLES ===
void afficherRegles(void) {
    effacerEcran();
    changerCouleur(COULEUR_VERT);
    printf("\n╔═══════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                           RÈGLES DU JEU - ECE HEROES                          ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════════════════╝\n\n");

    changerCouleur(COULEUR_JAUNE); printf("═══ OBJECTIF DU JEU ═══\n");
    changerCouleur(COULEUR_BLANC);
    printf("  Vous disposez d'un nombre limité de vies pour gagner tous les niveaux.\n");
    printf("  Pour gagner un niveau, vous devez remplir un CONTRAT en un temps limité\n");
    printf("  et avec un nombre maximum de coups.\n\n");

    changerCouleur(COULEUR_JAUNE); printf("═══ DÉROULEMENT D'UN NIVEAU ═══\n");
    changerCouleur(COULEUR_BLANC);
    printf("  • Le plateau de jeu est un tableau de 20 lignes x 15 colonnes (le plateau 25x45 n'est pas adapté)\n");
    printf("  • Au début, les cases sont remplies aléatoirement avec 5 types d'items\n");
    printf("  • Chaque niveau a un CONTRAT différent (exemple: 20 fraises, 50 oignons)\n");
    printf("  • Vous devez éliminer le nombre requis d'items en formant des figures\n");
    printf("  • Si vous perdez un niveau, vous perdez une vie\n\n");

    changerCouleur(COULEUR_JAUNE); printf("═══ FIGURES SPÉCIALES ET ÉLIMINATIONS ═══\n");
    changerCouleur(COULEUR_BLANC);

    changerCouleur(COULEUR_ROUGE); printf("  1. Suite de 6 items alignés (horizontal/vertical):\n");
    changerCouleur(COULEUR_BLANC); printf("     → Élimine TOUS les items du même type sur tout le plateau\n\n");

    changerCouleur(COULEUR_ROUGE); printf("  2. Croix de 9 items:\n");
    changerCouleur(COULEUR_BLANC); printf("     → Élimine tous les items du même type sur la ligne ET la colonne\n");
    printf("        (même les items isolés)\n\n");

    changerCouleur(COULEUR_ROUGE); printf("  3. Carré de 4x4 items identiques:\n");
    changerCouleur(COULEUR_BLANC); printf("     → Élimine tous les items du même type contenus dans le carré\n\n");

    changerCouleur(COULEUR_ROUGE); printf("  4. Suite de 4 items alignés (horizontal/vertical):\n");
    changerCouleur(COULEUR_BLANC); printf("     → Élimine les 4 items de la suite\n\n");

    changerCouleur(COULEUR_JAUNE); printf("═══ GRAVITÉ ET REMPLISSAGE ═══\n");
    changerCouleur(COULEUR_BLANC);
    printf("  • Quand des items sont éliminés, les items au-dessus tombent\n");
    printf("  • Les cases vides en haut sont remplies par de nouveaux items aléatoires\n");
    printf("  • Les règles de suppression s'appliquent automatiquement jusqu'à stabilisation\n\n");

    changerCouleur(COULEUR_JAUNE); printf("═══ COMMENT JOUER ═══\n");
    changerCouleur(COULEUR_BLANC);
    printf("  1. Déplacez-vous avec "); changerCouleur(COULEUR_CYAN); printf("Z/Q/S/D"); changerCouleur(COULEUR_BLANC);
    printf(" ou les "); changerCouleur(COULEUR_CYAN); printf("FLÈCHES\n"); changerCouleur(COULEUR_BLANC);
    printf("  2. Sélectionnez un item avec "); changerCouleur(COULEUR_CYAN); printf("ESPACE\n"); changerCouleur(COULEUR_BLANC);
    printf("  3. Choisissez un item voisin (haut/bas/gauche/droite) pour permuter\n");
    printf("  4. Si la permutation forme une figure spéciale, les items sont éliminés\n");
    printf("  5. Chaque permutation compte pour 1 coup\n\n");

    changerCouleur(COULEUR_JAUNE); printf("═══ VICTOIRE / DÉFAITE ═══\n");
    changerCouleur(COULEUR_BLANC);
    printf("  "); changerCouleur(COULEUR_VERT); printf("VICTOIRE: "); changerCouleur(COULEUR_BLANC);
    printf("Vous remplissez votre contrat avant la fin du temps/coups\n");
    printf("  "); changerCouleur(COULEUR_ROUGE); printf("DÉFAITE:  "); changerCouleur(COULEUR_BLANC);
    printf("Le temps ou les coups sont épuisés → Vous perdez 1 vie\n");
    printf("  "); changerCouleur(COULEUR_ROUGE); printf("GAME OVER:"); changerCouleur(COULEUR_BLANC);
    printf(" Vous n'avez plus de vies\n\n");

    changerCouleur(COULEUR_JAUNE); printf("═══ SAUVEGARDE ═══\n");
    changerCouleur(COULEUR_BLANC);
    printf("  • À la fin d'un niveau, vous pouvez sauvegarder votre progression\n");
    printf("  • Indiquez un pseudo pour enregistrer votre dernier niveau gagné\n");
    printf("  • Vous pourrez reprendre au niveau sauvegardé avec vos vies restantes\n\n");

    changerCouleur(COULEUR_CYAN);
    printf("╔═══════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║               Appuyez sur une touche pour revenir au menu...                  ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════════════════╝\n");
    changerCouleur(COULEUR_RESET);

    getch(); // Attente
}
