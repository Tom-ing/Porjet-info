#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "affichage.h"
#include <conio.h>

// Fonction pour changer la couleur du texte
void changerCouleur(int couleur) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, couleur);
}

// Fonction pour positionner le curseur
void allerA(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Fonction pour effacer l'écran
void effacerEcran(void) {
    system("cls"); // permet d'écrire directement dans l'invite de commande CLear Screen
}

// Affiche le menu principal
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
    
    changerCouleur(COULEUR_JAUNE);
    printf("        1. ");
    changerCouleur(COULEUR_BLANC);
    printf("Lire les règles du jeu\n\n");
    
    changerCouleur(COULEUR_JAUNE);
    printf("        2. ");
    changerCouleur(COULEUR_BLANC);
    printf("Commencer une nouvelle partie\n\n");
    
    changerCouleur(COULEUR_JAUNE);
    printf("        3. ");
    changerCouleur(COULEUR_BLANC);
    printf("Reprendre une partie sauvegardée\n\n");
    
    changerCouleur(COULEUR_JAUNE);
    printf("        4. ");
    changerCouleur(COULEUR_BLANC);
    printf("Quitter\n\n");
    
    changerCouleur(COULEUR_CYAN);
    printf("    >> Votre choix : ");
    changerCouleur(COULEUR_RESET);
}

// Affiche les règles du jeu
void afficherRegles(void) {
    effacerEcran();
    changerCouleur(COULEUR_VERT);
    printf("\n╔═══════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                           RÈGLES DU JEU - ECE HEROES                          ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════════════════╝\n\n");

    changerCouleur(COULEUR_JAUNE);
    printf("═══ OBJECTIF DU JEU ═══\n");
    changerCouleur(COULEUR_BLANC);
    printf("  Vous disposez d'un nombre limité de vies pour gagner tous les niveaux.\n");
    printf("  Pour gagner un niveau, vous devez remplir un CONTRAT en un temps limité\n");
    printf("  et avec un nombre maximum de coups.\n\n");

    changerCouleur(COULEUR_JAUNE);
    printf("═══ DÉROULEMENT D'UN NIVEAU ═══\n");
    changerCouleur(COULEUR_BLANC);
    printf("  • Le plateau de jeu est un tableau de 20 lignes x 20 colonnes (le plateau 25x45 n'est pas adapté)\n");
    printf("  • Au début, les cases sont remplies aléatoirement avec 5 types d'items\n");
    printf("  • Chaque niveau a un CONTRAT différent (exemple: 20 fraises, 50 oignons)\n");
    printf("  • Vous devez éliminer le nombre requis d'items en formant des figures\n");
    printf("  • Si vous perdez un niveau, vous perdez une vie\n\n");

    changerCouleur(COULEUR_JAUNE);
    printf("═══ FIGURES SPÉCIALES ET ÉLIMINATIONS ═══\n");
    changerCouleur(COULEUR_BLANC);

    changerCouleur(COULEUR_ROUGE);
    printf("  1. Suite de 6 items alignés (horizontal/vertical):\n");
    changerCouleur(COULEUR_BLANC);
    printf("     → Élimine TOUS les items du même type sur tout le plateau\n\n");

    changerCouleur(COULEUR_ROUGE);
    printf("  2. Croix de 9 items:\n");
    changerCouleur(COULEUR_BLANC);
    printf("     → Élimine tous les items du même type sur la ligne ET la colonne\n");
    printf("        (même les items isolés)\n\n");

    changerCouleur(COULEUR_ROUGE);
    printf("  3. Carré de 4x4 items identiques:\n");
    changerCouleur(COULEUR_BLANC);
    printf("     → Élimine tous les items du même type contenus dans le carré\n\n");

    changerCouleur(COULEUR_ROUGE);
    printf("  4. Suite de 4 items alignés (horizontal/vertical):\n");
    changerCouleur(COULEUR_BLANC);
    printf("     → Élimine les 4 items de la suite\n\n");

    changerCouleur(COULEUR_JAUNE);
    printf("═══ GRAVITÉ ET REMPLISSAGE ═══\n");
    changerCouleur(COULEUR_BLANC);
    printf("  • Quand des items sont éliminés, les items au-dessus tombent\n");
    printf("  • Les cases vides en haut sont remplies par de nouveaux items aléatoires\n");
    printf("  • Les règles de suppression s'appliquent automatiquement jusqu'à stabilisation\n\n");

    changerCouleur(COULEUR_JAUNE);
    printf("═══ COMMENT JOUER ═══\n");
    changerCouleur(COULEUR_BLANC);
    printf("  1. Déplacez-vous avec ");
    changerCouleur(COULEUR_CYAN);
    printf("Z/Q/S/D");
    changerCouleur(COULEUR_BLANC);
    printf(" ou les ");
    changerCouleur(COULEUR_CYAN);
    printf("FLÈCHES\n");
    changerCouleur(COULEUR_BLANC);
    printf("  2. Sélectionnez un item avec ");
    changerCouleur(COULEUR_CYAN);
    printf("ESPACE\n");
    changerCouleur(COULEUR_BLANC);
    printf("  3. Choisissez un item voisin (haut/bas/gauche/droite) pour permuter\n");
    printf("  4. Si la permutation forme une figure spéciale, les items sont éliminés\n");
    printf("  5. Chaque permutation compte pour 1 coup\n\n");

    changerCouleur(COULEUR_JAUNE);
    printf("═══ VICTOIRE / DÉFAITE ═══\n");
    changerCouleur(COULEUR_BLANC);
    printf("  ");
    changerCouleur(COULEUR_VERT);
    printf("VICTOIRE: ");
    changerCouleur(COULEUR_BLANC);
    printf("Vous remplissez votre contrat avant la fin du temps/coups\n");
    printf("  ");
    changerCouleur(COULEUR_ROUGE);
    printf("DÉFAITE:  ");
    changerCouleur(COULEUR_BLANC);
    printf("Le temps ou les coups sont épuisés → Vous perdez 1 vie\n");
    printf("  ");
    changerCouleur(COULEUR_ROUGE);
    printf("GAME OVER:");
    changerCouleur(COULEUR_BLANC);
    printf(" Vous n'avez plus de vies\n\n");

    changerCouleur(COULEUR_JAUNE);
    printf("═══ SAUVEGARDE ═══\n");
    changerCouleur(COULEUR_BLANC);
    printf("  • À la fin d'un niveau, vous pouvez sauvegarder votre progression\n");
    printf("  • Indiquez un pseudo pour enregistrer votre dernier niveau gagné\n");
    printf("  • Vous pourrez reprendre au niveau sauvegardé avec vos vies restantes\n\n");

    changerCouleur(COULEUR_CYAN);
    printf("╔═══════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║               Appuyez sur une touche pour revenir au menu...                  ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════════════════╝\n");
    changerCouleur(COULEUR_RESET);
}

// Affiche l'écran de jeu complet
void afficherNiveauJeu(Partie* partie, int curseurX, int curseurY, int selectX, int selectY) {
    effacerEcran();

    // --- 1. Titre ---
    // (On le garde simple, en haut)
    changerCouleur(COULEUR_JAUNE);
    printf("╔════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║");
    changerCouleur(COULEUR_JAUNE);
    printf("                                ECE HEROES - NIVEAU %d                               ", partie->niveau);
    changerCouleur(COULEUR_JAUNE);
    printf("║\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════════╝\n\n");


    // --- 2. Définition du Layout ---
    int plateauX = 3;  // Marge gauche
    int plateauY = 5;  // Sous le titre

    // HAUTEUR = 20. LARGEUR = 20.
    // Chaque item fait 4 chars (" %-2s ")
    int hauteurPlateau = HAUTEUR + 2; // 20 items + 2 bordures
    int largeurPlateau = (LARGEUR * 4) + 2; // (20 * 4) + 2 = 82

    // Le HUD (Stats) se place à droite du plateau
    int statsX = plateauX + largeurPlateau + 3; // 3 espaces
    int statsY = plateauY;

    // Les contrôles se placent SOUS le plateau
    int controlesY = plateauY + hauteurPlateau + 2; // 2 lignes sous le plateau
    int controlesX = plateauX;

    // La légende se place SOUS les contrôles
    int legendeY = controlesY + 5; // 5 lignes pour les contrôles
    int legendeX = plateauX;

    // --- 3. Dessin des éléments ---
    afficherPlateau(partie, curseurX, curseurY, selectX, selectY, plateauX, plateauY);
    afficherStats(partie, statsX, statsY);
    afficherControles(controlesX, controlesY);
    afficherLegende(legendeX, legendeY);

    changerCouleur(COULEUR_RESET);
}

// Affiche le plateau de jeu
void afficherPlateau(Partie* partie, int curseurX, int curseurY, int selectX, int selectY, int startX, int startY) {
    int tableau[HAUTEUR][LARGEUR];
    memcpy(tableau, partie->tableau, sizeof(partie->tableau));

    char* symboles[] = {" ", "🍓", "🧅", "🍊", "🍇", "🥕", "💣", "🧱"};
    int couleurs[] = {COULEUR_RESET, COULEUR_ROUGE, COULEUR_VIOLET, COULEUR_ORANGE, COULEUR_VIOLET, COULEUR_ORANGE, COULEUR_BLANC};

    int H = HAUTEUR; // 20
    int L = LARGEUR; // 20
    int itemWidth = 4; // Largeur de " %-2s "

    // --- 1. Dessin du Contour ---
    changerCouleur(COULEUR_JAUNE);

    // Coin HAUT-GAUCHE
    allerA(startX, startY);
    printf("╔");

    // Ligne HAUT (Largeur = 20 items * 4 chars)
    for (int j = 0; j < (L * itemWidth); j++) printf("═");

    // Coin HAUT-DROITE
    printf("╗");

    // Côtés GAUCHE et DROITE
    for (int i = 0; i < H; i++) {
        allerA(startX, startY + 1 + i);
        printf("║"); // Côté gauche
        allerA(startX + (L * itemWidth) + 1, startY + 1 + i);
        printf("║"); // Côté droite
    }

    // Coin BAS-GAUCHE
    allerA(startX, startY + H + 1);
    printf("╚");

    // Ligne BAS
    for (int j = 0; j < (L * itemWidth); j++) printf("═");

    // Coin BAS-DROITE
    printf("╝");

    // --- 2. Dessin des Items ---
    for (int i = 0; i < H; i++) {
        // Se positionne pour la ligne
        allerA(startX + 1, startY + 1 + i);

        for (int j = 0; j < L; j++) {
            int item = tableau[i][j];
            char* s = symboles[item]; // symbole avec les emoji

            // On force une largeur de 4 pour chaque case
            if (i == curseurY && j == curseurX) {
                changerCouleur(COULEUR_BLANC); printf("[");
                changerCouleur(couleurs[item]); printf("%-2s", s); // 2 chars pour le symbole
                changerCouleur(COULEUR_BLANC); printf("]");
            }
            else if (i == selectY && j == selectX) {
                changerCouleur(COULEUR_JAUNE); printf("{");
                changerCouleur(couleurs[item]); printf("%-2s", s);
                changerCouleur(COULEUR_JAUNE); printf("}");
            }
            else {
                changerCouleur(couleurs[item]);
                printf(" %-2s ", s);
            }
        }
    }
}

// Affiche les statistiques
void afficherStats(Partie* partie, int startX, int startY) {
    // Les positions sont maintenant passées en paramètre
    int posX = startX;
    int posY = startY;

    allerA(posX, posY++);
    changerCouleur(COULEUR_JAUNE);
    printf("╔═════════════════════╗");

    allerA(posX, posY++);
    printf("║");
    changerCouleur(COULEUR_BLANC);
    printf(" VIES : ");
    changerCouleur(COULEUR_ROUGE);
    printf("%d / %d", partie->vies, NB_VIES_INITIAL);
    changerCouleur(COULEUR_JAUNE);
    printf("        ║");

    allerA(posX, posY++); // posY = 6
    printf("║");
    changerCouleur(COULEUR_BLANC);
    printf(" TEMPS : ");
    changerCouleur(COULEUR_CYAN);
    printf("%02d:%02d", partie->temps_restant / 60, partie->temps_restant % 60);
    changerCouleur(COULEUR_JAUNE);
    printf("       ║");

    allerA(posX, posY++); // posY = 7
    printf("║");
    changerCouleur(COULEUR_BLANC);
    printf(" COUPS : ");
    changerCouleur(COULEUR_CYAN);
    printf("%-3d", partie->coups_restants);
    changerCouleur(COULEUR_JAUNE);
    printf("         ║");

    allerA(posX, posY++); // posY = 8
    printf("╠═════════════════════╣");

    allerA(posX, posY++); // posY = 9
    printf("║");
    changerCouleur(COULEUR_VERT);
    printf("       CONTRAT     ");
    changerCouleur(COULEUR_JAUNE);
    printf("  ║");

    allerA(posX, posY++); // posY = 10
    printf("╠═════════════════════╣");

    char* symboles[] = {" ", "🍓", "🧅", "🍊", "🍇", "🥕", "💣", "🧱"};

    for (int i = 0; i < NB_TYPES_ITEMS; i++) {
        allerA(posX, posY++);
        printf("║   ");
        changerCouleur(COULEUR_BLANC);

        printf("[%s]  %3d / %-3d",
               symboles[i+1],
               partie->elimines[i],
               partie->contrat[i]);

        changerCouleur(COULEUR_JAUNE);
        printf("   ║");
    }

    allerA(posX, posY++);
    printf("╚═════════════════════╝");

    changerCouleur(COULEUR_RESET);
}

// Affiche les contrôles
void afficherControles(int startX, int startY) {
    int X = startX;
    int Y = startY;
    int W = 96;

    changerCouleur(COULEUR_VERT);

    allerA(X, Y++);
    printf("╔");
    for (int j = 0; j < W - 2; j++) printf("═");
    printf("╗");

    allerA(X, Y++);
    printf("║ ");
    changerCouleur(COULEUR_JAUNE);
    printf("CONTRÔLES");
    changerCouleur(COULEUR_VERT);
    allerA(X + W - 1, Y - 1);
    printf("║");

    allerA(X, Y++);
    printf("║ ");
    changerCouleur(COULEUR_BLANC); printf("Déplacement: ");
    changerCouleur(COULEUR_CYAN);  printf("[Z/Q/S/D]");
    changerCouleur(COULEUR_BLANC);  printf(" ou ");
    changerCouleur(COULEUR_CYAN);  printf("[Flèches]");

    changerCouleur(COULEUR_BLANC); printf(" | Sélection: ");
    changerCouleur(COULEUR_CYAN);  printf("[ESPACE]");

    changerCouleur(COULEUR_BLANC); printf(" | Quitter: ");
    changerCouleur(COULEUR_CYAN);  printf("[ECHAP]");

    changerCouleur(COULEUR_VERT);
    // Astuce : On va directement à la fin de la ligne pour fermer la boîte
    // Cela évite tout décalage même si le texte change de longueur
    allerA(X + W - 1, Y - 1);
    printf("║");

    allerA(X, Y++);
    printf("╚");
    for (int j = 0; j < W - 2; j++) printf("═");
    printf("╝");
}

// Affiche la légende
void afficherLegende(int startX, int startY) {
    allerA(startX, startY); // Se positionne

    changerCouleur(COULEUR_BLANC);
    printf("Légende: ");

    changerCouleur(COULEUR_ROUGE); printf("[🍓]");
    changerCouleur(COULEUR_BLANC); printf("=Fraise  ");

    changerCouleur(COULEUR_JAUNE); printf("[🧅]");
    changerCouleur(COULEUR_BLANC); printf("=Oignon  ");

    changerCouleur(COULEUR_ORANGE); printf("[🍊]");
    changerCouleur(COULEUR_BLANC); printf("=Mandarine  ");

    changerCouleur(COULEUR_VIOLET); printf("[🍇]");
    changerCouleur(COULEUR_BLANC); printf("=Raisin  ");

    changerCouleur(COULEUR_ORANGE); printf("[🥕]");
    changerCouleur(COULEUR_BLANC); printf("=Carotte");
}

// Affiche un message de victoire
void afficherVictoire(void) {
    effacerEcran();

    int posX = 20;
    int posY = 5;

    changerCouleur(COULEUR_JAUNE);
    allerA(posX, posY++); printf("             ___________");
    allerA(posX, posY++); printf("            '._==_==_=_.'");
    allerA(posX, posY++); printf("            .-\\:      /-.");
    allerA(posX, posY++); printf("           | (|:.     |) |");
    allerA(posX, posY++); printf("            '-|:.     |-'");
    allerA(posX, posY++); printf("              \\::.    /");
    allerA(posX, posY++); printf("               '::. .'");
    allerA(posX, posY++); printf("                 ) (");
    allerA(posX, posY++); printf("               _.' '._");
    allerA(posX, posY++); printf("              `\"\"\"\"\"\"\"`");

    int textY = posY + 2;

    for (int i = 0; i < 10; i++) { // 10 clignotements
        allerA(posX - 5, textY);

        if (i % 2 == 0) {
            changerCouleur(COULEUR_VERT);
            printf("    >>>   N I V E A U   R É U S S I   <<<    ");
        } else {
            changerCouleur(COULEUR_BLANC);
            printf("    >>>   N I V E A U   R É U S S I   <<<    ");
        }

        Sleep(150); // Pause agréable
    }

    changerCouleur(COULEUR_CYAN);
    allerA(posX - 2, textY + 3);
    printf("Appuyez sur une touche pour continuer...");
    changerCouleur(COULEUR_RESET);
}

//Affiche Animation Défaite
void afficherDefaite(void) {
    effacerEcran();

    int posX = 20;
    int posY = 5;

    changerCouleur(COULEUR_BLANC);
    allerA(posX, posY++); printf("      _.--\"\"--._");
    allerA(posX, posY++); printf("     /  _    _  \\");
    allerA(posX, posY++); printf("  _  ( (0)  (0) )  _");
    allerA(posX, posY++); printf(" { \\  \\    ^    /  / }");
    allerA(posX, posY++); printf("  \\ \\  \\  \\-   /  / /");
    allerA(posX, posY++); printf("   \\ \\  ~\"\"\"\"~  / /");
    allerA(posX, posY++); printf("    \\_           _/");
    allerA(posX, posY++); printf("      |--.....--|");

    int textY = posY + 2;

    for (int i = 0; i < 10; i++) {
        allerA(posX - 2, textY);

        if (i % 2 == 0) {
            changerCouleur(COULEUR_ROUGE);
            printf("    !!!   G A M E   O V E R   !!!    ");
        } else {
            changerCouleur(COULEUR_ROUGE);
            // Ici on alterne Rouge / Gris sombre pour l'effet alarme
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); // Rouge sombre
            printf("    !!!   G A M E   O V E R   !!!    ");
        }
        Sleep(150);
    }

    changerCouleur(COULEUR_CYAN);
    allerA(posX, textY + 3);
    printf("Appuyez sur une touche...");
    changerCouleur(COULEUR_RESET);
}

// Affiche l'écran final
void afficherEcranFinJeu(void) {
    effacerEcran();

    int posX = 40;
    int posY = 5;

    int couleurs[] = {COULEUR_JAUNE, COULEUR_ORANGE, COULEUR_ROUGE, COULEUR_VIOLET, COULEUR_CYAN, COULEUR_VERT};
    int nbCouleurs = 6;
    int frame = 0;

    while (!kbhit()) {

        int couleurActuelle = couleurs[frame % nbCouleurs];
        changerCouleur(couleurActuelle);

        int y = posY;
        allerA(posX, y++); printf("                   .-=========-.                    ");
        allerA(posX, y++); printf("                   \\'-=======-'/                    ");
        allerA(posX, y++); printf("                   _|   .=.   |_                    ");
        allerA(posX, y++); printf("                  ((|  {{1}}  |))                   ");
        allerA(posX, y++); printf("                   \\|   /|\\   |/                    ");
        allerA(posX, y++); printf("                    \\__ '`' __/                     ");
        allerA(posX, y++); printf("                      _`) (`_                       ");
        allerA(posX, y++); printf("                    _/_______\\_                     ");
        allerA(posX, y++); printf("                   /___________\\                    ");

        y += 1; // Petit espace


        allerA(posX, y++); printf("   ___  _  _   _   __  __  ___  ___   ___  _  _  ");
        allerA(posX, y++); printf("  / __|| || | /_\\ |  \\/  || _ \\|_ _| / _ \\| \\| | ");
        allerA(posX, y++); printf(" | (__ | __ |/ _ \\| |\\/| ||  _/ | |   (_) | .` | ");
        allerA(posX, y++); printf("  \\___||_||_/_/ \\_\\_|  |_||_|  |___| \\___/|_|\\_| ");

        // 4. Le message de bas de page
        changerCouleur(COULEUR_CYAN); // On garde le bas en blanc pour la lisibilité
        allerA(posX + 5, y + 4);
        printf(">>> APPUYEZ SUR UNE TOUCHE POUR QUITTER <<<");

        Sleep(150);
        frame++;
    }

    // Consomme la touche pressée
    getch();

    // Reset
    changerCouleur(COULEUR_RESET);
    effacerEcran();
}

// Affiche un message temporaire
void afficherMessageTemporaire(char* message) {
    changerCouleur(COULEUR_JAUNE);
    printf("\n  >> %s\n", message);
    changerCouleur(COULEUR_RESET);
}

// Rafraîchit UNIQUEMENT le timer, sans effacer l'écran.
void rafraichirTimerSeulement(Partie* partie) {
    int posX = 67;
    int posY = 7; // Ligne TEMPS

    // (posX(67) + 11 chars pour que le temps soit aligner à "TEMPS"
    int chiffresX = posX + 11;

    // on se positionne
    allerA(chiffresX, posY);

    // pour toujours avoir 2 chiffre par exemple 01:30 à la place de 1:30
    changerCouleur(COULEUR_CYAN);
    printf("%02d:%02d", partie->temps_restant / 60, partie->temps_restant % 60);

    allerA(0, 0);
}
