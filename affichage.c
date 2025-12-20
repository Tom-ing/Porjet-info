#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include "affichage.h"

// Définition statique des symboles pour ne pas surcharger la mémoire
// Source : Assistant IA (Optimisation mémoire)
static const char* SYMBOLES[] = {" ", "🍓", "🧅", "🍊", "🍇", "🥕", "💣", "🧱", "🦠"};
static const int COULEURS_ITEMS[] = {
    COULEUR_RESET,
    COULEUR_ROUGE, COULEUR_VIOLET, COULEUR_ORANGE, COULEUR_VIOLET, COULEUR_ORANGE,
    COULEUR_BLANC, // Bombe
    COULEUR_BLANC,  // Mur
    COULEUR_VERT   // Virus
};

// === FONCTIONS UTILITAIRES WINDOWS ===
// Source : Documentation Windows.h / Assistant IA
// Permet de manipuler la console (Couleurs, Position du curseur).

void changerCouleur(int couleur) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, couleur);
}

void allerA(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void effacerEcran(void) {
    system("cls");
}
// Rôle : Cache le trait clignotant de la console pour faire plus "Jeu Vidéo"
void masquerCurseur(void) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO infos;

    GetConsoleCursorInfo(hConsole, &infos); // On récupère les infos actuelles
    infos.bVisible = FALSE;                 // On met la visibilité à FAUX
    SetConsoleCursorInfo(hConsole, &infos); // On applique
}

// === AFFICHAGE DU JEU (HUB) ===
// Rôle : Fonction principale qui appelle toutes les sous-fonctions d'affichage (Plateau, Stats, etc.)
void afficherNiveauJeu(Partie* partie, int curseurX, int curseurY, int selectX, int selectY) {
    effacerEcran();

    // 1. Titre
    changerCouleur(COULEUR_VERT);
    printf("╔════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                ECE HEROES - NIVEAU %d                               ║\n", partie->niveau);
    printf("╚════════════════════════════════════════════════════════════════════════════════════╝\n\n");

    // 2. Calcul des positions
    int plateauX = 3;
    int plateauY = 5;

    int largeurPlateau = (LARGEUR * 4) + 2;
    int hauteurPlateau = HAUTEUR + 2;

    int statsX = plateauX + largeurPlateau + 3;
    int statsY = plateauY;
    int controlesY = plateauY + hauteurPlateau + 2;
    int controlesX = plateauX;
    int legendeY = controlesY + 5;
    int legendeX = plateauX;

    // 3. Dessin des composants
    afficherPlateau(partie, curseurX, curseurY, selectX, selectY, plateauX, plateauY);
    afficherStats(partie, statsX, statsY);
    afficherControles(controlesX, controlesY);
    afficherLegende(legendeX, legendeY);

    changerCouleur(COULEUR_RESET);
}

// === AFFICHAGE DE LA GRILLE (PLATEAU) ===
// Rôle : Dessine le tableau avec les fruits, les bordures et gère le curseur.
// Note : Les bordures sont forcées en JAUNE fixe.
void afficherPlateau(Partie* partie, int curseurX, int curseurY, int selectX, int selectY, int startX, int startY) {
    int largeurCase = 4;

    // --- DESSIN DES BORDURES EXTÉRIEURES ---
    changerCouleur(COULEUR_JAUNE);

    // Cadre Haut
    allerA(startX, startY);
    printf("╔");
    for (int j = 0; j < (LARGEUR * largeurCase); j++) printf("═");
    printf("╗");

    // Côtés (Gauche et Droite)
    for (int i = 0; i < HAUTEUR; i++) {
        allerA(startX, startY + 1 + i); printf("║");
        allerA(startX + (LARGEUR * largeurCase) + 1, startY + 1 + i); printf("║");
    }

    // Cadre Bas
    allerA(startX, startY + HAUTEUR + 1);
    printf("╚");
    for (int j = 0; j < (LARGEUR * largeurCase); j++) printf("═");
    printf("╝");

    // --- DESSIN DU CONTENU (FRUITS) ---
    for (int i = 0; i < HAUTEUR; i++) {
        allerA(startX + 1, startY + 1 + i);

        for (int j = 0; j < LARGEUR; j++) {
            int item = partie->tableau[i][j];

            // Gestion visuelle du curseur [ ] et de la sélection { }
            if (i == curseurY && j == curseurX) {
                changerCouleur(COULEUR_BLANC); printf("[");
                changerCouleur(COULEURS_ITEMS[item]); printf("%-2s", SYMBOLES[item]);
                changerCouleur(COULEUR_BLANC); printf("]");
            }
            else if (i == selectY && j == selectX) {
                changerCouleur(COULEUR_JAUNE); printf("{");
                changerCouleur(COULEURS_ITEMS[item]); printf("%-2s", SYMBOLES[item]);
                changerCouleur(COULEUR_JAUNE); printf("}");
            }
            else {
                changerCouleur(COULEURS_ITEMS[item]);
                printf(" %-2s ", SYMBOLES[item]);
            }
        }
    }
    // On remet la couleur normale après avoir dessiné
    changerCouleur(COULEUR_RESET);
}

// === AFFICHAGE DES STATISTIQUES (HUD) ===
void afficherStats(Partie* partie, int startX, int startY) {
    int posX = startX;
    int posY = startY;

    allerA(posX, posY++);
    changerCouleur(COULEUR_JAUNE); printf("╔═════════════════════╗");

    allerA(posX, posY++);
    printf("║"); changerCouleur(COULEUR_BLANC); printf(" VIES : ");
    changerCouleur(COULEUR_ROUGE); printf("%d / %d", partie->vies, NB_VIES_INITIAL);
    changerCouleur(COULEUR_JAUNE); printf("        ║");

    allerA(posX, posY++);
    printf("║"); changerCouleur(COULEUR_BLANC); printf(" TEMPS : ");
    changerCouleur(COULEUR_CYAN);  printf("%02d:%02d", partie->temps_restant / 60, partie->temps_restant % 60);
    changerCouleur(COULEUR_JAUNE); printf("       ║");

    allerA(posX, posY++);
    printf("║"); changerCouleur(COULEUR_BLANC); printf(" COUPS : ");
    changerCouleur(COULEUR_CYAN);  printf("%-3d", partie->coups_restants);
    changerCouleur(COULEUR_JAUNE); printf("         ║");

    allerA(posX, posY++); printf("╠═════════════════════╣");
    allerA(posX, posY++);
    printf("║"); changerCouleur(COULEUR_VERT); printf("       CONTRAT     "); changerCouleur(COULEUR_JAUNE); printf("  ║");
    allerA(posX, posY++); printf("╠═════════════════════╣");

    // Affichage dynamique des contrats (Objectifs)
    for (int i = 0; i < NB_TYPES_ITEMS; i++) {
        allerA(posX, posY++);
        printf("║   ");
        changerCouleur(COULEUR_BLANC);
        printf("[%s]  %3d / %-3d", SYMBOLES[i+1], partie->elimines[i], partie->contrat[i]);
        changerCouleur(COULEUR_JAUNE); printf("   ║");
    }

    allerA(posX, posY++); printf("╚═════════════════════╝");
    changerCouleur(COULEUR_RESET);
}

// === AFFICHAGE DES CONTRÔLES (Bas de page) ===
void afficherControles(int startX, int startY) {
    int X = startX;
    int Y = startY;
    int W = 75; // Largeur de la boîte

    changerCouleur(COULEUR_VERT);
    allerA(X, Y++); printf("╔"); for (int j = 0; j < W - 2; j++) printf("═"); printf("╗");
    allerA(X, Y++); printf("║ ");

    changerCouleur(COULEUR_JAUNE); printf("CONTRÔLES"); changerCouleur(COULEUR_VERT);
    allerA(X + W - 1, Y - 1); printf("║");

    allerA(X, Y++); printf("║ ");
    changerCouleur(COULEUR_BLANC); printf("Déplacement: "); changerCouleur(COULEUR_CYAN); printf("[Z/Q/S/D]");
    changerCouleur(COULEUR_BLANC); printf(" | Sélection: "); changerCouleur(COULEUR_CYAN); printf("[ESPACE]");
    changerCouleur(COULEUR_BLANC); printf(" | Quitter: "); changerCouleur(COULEUR_CYAN); printf("[ECHAP]");

    changerCouleur(COULEUR_VERT);
    allerA(X + W - 1, Y - 1); printf("║");

    allerA(X, Y++); printf("╚"); for (int j = 0; j < W - 2; j++) printf("═"); printf("╝");
}

void afficherLegende(int startX, int startY) {
    allerA(startX, startY);
    changerCouleur(COULEUR_BLANC); printf("Légende: ");
    changerCouleur(COULEUR_ROUGE); printf("[🍓]=Fraise  ");
    changerCouleur(COULEUR_JAUNE); printf("[🧅]=Oignon  ");
    changerCouleur(COULEUR_ORANGE); printf("[🍊]=Mandarine  ");
    changerCouleur(COULEUR_VIOLET); printf("[🍇]=Raisin  ");
    changerCouleur(COULEUR_ORANGE); printf("[🥕]=Carotte");
}

void afficherVictoire(void) {
    effacerEcran();
    int posX = 20; int posY = 5;
    changerCouleur(COULEUR_JAUNE);
    allerA(posX, posY++); printf("             ___________");
    allerA(posX, posY++); printf("            '._==_==_=_.'");
    allerA(posX, posY++); printf("            .-\\:      /-.");
    allerA(posX, posY++); printf("           | (|:.     |) |");
    allerA(posX, posY++); printf("            '-|:.     |-'");

    int textY = posY + 2;
    for (int i = 0; i < 6; i++) {
        allerA(posX - 5, textY);
        if (i % 2 == 0) changerCouleur(COULEUR_VERT); else changerCouleur(COULEUR_BLANC);
        printf("    >>>   N I V E A U   R É U S S I   <<<    ");
        Sleep(150);
    }
    changerCouleur(COULEUR_CYAN);
    allerA(posX - 2, textY + 3);
    printf("Appuyez sur une touche pour continuer...");
    changerCouleur(COULEUR_RESET);
}

void afficherDefaite(void) {
    effacerEcran();
    int posX = 20; int posY = 5;
    changerCouleur(COULEUR_BLANC);
    allerA(posX, posY++); printf("      _.--\"\"--._");
    allerA(posX, posY++); printf("     /  _    _  \\");
    allerA(posX, posY++); printf("  _  ( (0)  (0) )  _");

    int textY = posY + 3;
    for (int i = 0; i < 6; i++) {
        allerA(posX - 2, textY);
        changerCouleur(COULEUR_ROUGE);
        printf("    !!!   G A M E   O V E R   !!!    ");
        Sleep(150);
    }
    changerCouleur(COULEUR_CYAN);
    allerA(posX, textY + 3);
    printf("Appuyez sur une touche...");
    changerCouleur(COULEUR_RESET);
}

void afficherEcranFinJeu(void) {
    effacerEcran();
    int posX = 40; int posY = 5;
    int couleurs[] = {COULEUR_JAUNE, COULEUR_ORANGE, COULEUR_ROUGE, COULEUR_VIOLET, COULEUR_CYAN, COULEUR_VERT};
    int frame = 0;

    // Animation finale
    while (!kbhit()) {
        changerCouleur(couleurs[frame % 6]);
        int y = posY;
        allerA(posX, y++); printf("   ___  _  _   _   __  __  ___  ___   ___  _  _  ");
        allerA(posX, y++); printf("  / __|| || | /_\\ |  \\/  || _ \\|_ _| / _ \\| \\| | ");
        allerA(posX, y++); printf(" | (__ | __ |/ _ \\| |\\/| ||  _/ | |   (_) | .` | ");
        allerA(posX, y++); printf("  \\___||_||_/_/ \\_\\_|  |_||_|  |___| \\___/|_|\\_| ");

        changerCouleur(COULEUR_CYAN);
        allerA(posX + 5, y + 4);
        printf(">>> APPUYEZ SUR UNE TOUCHE POUR QUITTER <<<");
        Sleep(150);
        frame++;
    }
    getch();
    changerCouleur(COULEUR_RESET);
    effacerEcran();
}

void afficherMessageTemporaire(char* message) {
    changerCouleur(COULEUR_JAUNE);
    printf("\n  >> %s\n", message);
    changerCouleur(COULEUR_RESET);
}

// Source : Assistant IA (Algorithme d'optimisation)
// Rôle : Ne rafraîchit que les chiffres du temps pour éviter le scintillement de l'écran.
void rafraichirTimerSeulement(Partie* partie) {
    int largeurPlateau = (LARGEUR * 4) + 2;
    int statsX = 3 + largeurPlateau + 3;

    // Position exacte des chiffres du Timer
    allerA(statsX + 11, 7);
    changerCouleur(COULEUR_CYAN);
    printf("%01d:%01d", partie->temps_restant / 60, partie->temps_restant % 60);
    allerA(0, 0);
}

// === DESSINER UNE CASE UNIQUE (Optimisation) ===
// Rôle : Met à jour l'affichage d'une seule case sans toucher au reste
void afficherUneCase(Partie* partie, int gridX, int gridY, int curseurX, int curseurY, int selectX, int selectY) {
    // 1. Définition des constantes de position (DOIT ÊTRE IDENTIQUE À afficherNiveauJeu)
    int plateauX = 3;
    int plateauY = 5;

    // 2. Calcul de la position exacte sur l'écran console
    // Chaque case fait 4 caractères de large (" [x] ")
    int screenX = plateauX + 1 + (gridX * 4);
    int screenY = plateauY + 1 + gridY;

    // 3. Récupération de l'item
    int item = partie->tableau[gridY][gridX];

    // Symboles (reprise de ta liste statique)
    const char* SYMBOLES[] = {" ", "🍓", "🧅", "🍊", "🍇", "🥕", "💣", "🧱", "🦠", "🌵"};
    const int COULEURS[] = {7, 12, 13, 6, 13, 6, 15, 15, 10, 10}; // Codes couleurs simples

    // 4. Déplacement du curseur console
    allerA(screenX, screenY);

    // 5. Dessin logique (Curseur vs Sélection vs Normal)
    if (gridY == curseurY && gridX == curseurX) {
        // C'est le curseur actuel
        changerCouleur(15); printf("["); // Blanc
        changerCouleur(COULEURS[item]); printf("%-2s", SYMBOLES[item]);
        changerCouleur(15); printf("]");
    }
    else if (gridY == selectY && gridX == selectX) {
        // C'est l'item sélectionné pour échange
        changerCouleur(14); printf("{"); // Jaune
        changerCouleur(COULEURS[item]); printf("%-2s", SYMBOLES[item]);
        changerCouleur(14); printf("}");
    }
    else {
        // Case normale
        changerCouleur(COULEURS[item]);
        printf(" %-2s ", SYMBOLES[item]);
    }

    changerCouleur(7); // Reset couleur
    allerA(0, 0);
}

// === FONCTION DE SAISIE SÉCURISÉE ===
// Source : Assistant IA (Alternative sécurisée à scanf pour l'interface graphique)
// Rôle : Permet de taper son pseudo sans faire planter l'affichage graphique.
// Entrée : Le tableau où stocker le texte (buffer) et sa taille max.
// Sortie : Aucune (modifie directement le buffer).
void saisirPseudo(char* buffer, int longueurMax) {
    int i = 0; char c;
    memset(buffer, 0, longueurMax);
    while (1) {
        c = getch();
        if (c == 13) break;
        else if (c == 8) { if (i > 0) { i--; printf("\b \b"); buffer[i] = '\0'; } }
        else if (i < longueurMax - 1 && c >= 32 && c <= 126) { buffer[i] = c; i++; printf("%c", c); }
    }
}
