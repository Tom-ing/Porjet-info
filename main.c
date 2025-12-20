#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#include "structures.h"
#include "affichage.h"
#include "moteur.h"
#include "sauvegarde.h"
#include "menupause.h"
#include "audio.h"
#include "regles.h"

// Prototypes locaux
int jouerNiveau(Partie* partie);
void lancerJeu(Partie* partie);

// === MAIN ===
// Rôle : Initialise le programme et gère la boucle du Menu Principal.
int main() {
    Partie partie;
    int continuer = 1;
    char pseudo[50];

    system("chcp 65001 > nul");
    masquerCurseur();

    while (continuer) {
        afficherMenuPrincipal();
        char touche = getch();

        switch (touche) {
            case '1': afficherRegles(); getch(); break;
            case '2': initialiserPartie(&partie); lancerJeu(&partie); break;
            case '3': // CHARGER
                effacerEcran();
            changerCouleur(COULEUR_CYAN);
            printf("\n  >> Entrez votre pseudo : ");
            changerCouleur(COULEUR_BLANC);
            saisirPseudo(pseudo, 50); // Appel depuis affichage.c

            if (chargerPartieComplete(pseudo, &partie)) {
                printf("\n\n  >> Partie en cours retrouvee !");
                Sleep(1500);
                lancerJeu(&partie);
            }
            else if (chargerPartie(pseudo, &partie.niveau, &partie.vies)) {
                printf("\n\n  >> Progression retrouvee !");
                Sleep(1500);
                genererNiveau(&partie, partie.niveau);
                lancerJeu(&partie);
            } else {
                printf("\n\n  >> Aucune sauvegarde trouvée.");
                Sleep(2000);
            }
            break;
            case '4': continuer = 0; break;
        }
    }
    return 0;
}

// === GESTIONNAIRE DE JEU ===
// Rôle : Gère l'enchaînement des niveaux (1 -> 2 -> 3) et la sauvegarde entre eux.
// Entrée : La structure Partie (pointeur).
// === GESTIONNAIRE DE JEU ===
void lancerJeu(Partie* partie) {
    char pseudo[50];

    // Lancement initial de la musique de fond
    lancerMusique("musique.mp3");

    // Boucle tant qu'on a des vies et qu'on n'a pas fini le jeu
    while (partie->vies > 0 && partie->niveau <= NB_NIVEAUX) {

        int resultat = jouerNiveau(partie);

        // --- CAS 1 : VICTOIRE DU NIVEAU ---
        if (resultat == 1) {

            // 1. Son et Message de Victoire
            jouerJingle("victoire.mp3"); // Coupe la musique et lance le jingle

            if (partie->niveau < NB_NIVEAUX) {
                afficherVictoire(); // Affiche "GAGNÉ" ou ton ASCII victoire

                // 2. On attend bien 4 secondes pour profiter de la musique
                Sleep(4000);

                // --- MENU DE SAUVEGARDE ---
                effacerEcran();
                changerCouleur(COULEUR_VERT);
                printf("\n\n    NIVEAU %d REUSSI !", partie->niveau);
                changerCouleur(COULEUR_JAUNE);
                printf("\n\n    Voulez-vous sauvegarder la progression ? (O/N) : ");

                // 3. IMPORTANT : On vide le buffer clavier avant de demander
                // Sinon le dernier mouvement du jeu risque de valider ce menu tout seul !
                while(kbhit()) getch();


                char choix = getch(); // On attend la vraie réponse du joueur

                if (choix == 'o' || choix == 'O') {
                    changerCouleur(COULEUR_CYAN);
                    printf("\n    Entrez un pseudo pour la sauvegarde : ");
                    changerCouleur(COULEUR_BLANC);
                    saisirPseudo(pseudo, 50);

                    sauvegarderPartie(pseudo, partie->niveau + 1, partie->vies);

                    changerCouleur(COULEUR_VERT);
                    printf("\n    Sauvegarde effectuée avec succès !");
                    Sleep(1500);
                }
            }

            // Gestion Passage Niveau Suivant / Fin Jeu
            if (partie->niveau == NB_NIVEAUX) {
                // C'est la fin totale du jeu
                afficherEcranFinJeu();
                Sleep(5000); // Temps pour la musique de fin
                break;
            } else {
                // On passe au niveau suivant
                partie->niveau++;
                effacerEcran();
                changerCouleur(COULEUR_VERT);
                printf("\n\n    CHARGEMENT DU NIVEAU %d...\n", partie->niveau);
                Sleep(2000);

                genererNiveau(partie, partie->niveau);

                // 4. TRES IMPORTANT : On relance la musique de fond
                lancerMusique("musique.mp3");
            }
        }

        // --- CAS 2 : ABANDON (Via menu pause) ---
        else if (resultat == -1) {
            break; // On retourne au menu principal directement
        }

        // --- CAS 3 : ECHEC DU NIVEAU ---
        else {
            // Le joueur a perdu ce niveau. On regarde s'il lui reste des vies.

            if (partie->vies > 0) {

                jouerJingle("gameover.mp3");
                effacerEcran();
                changerCouleur(COULEUR_ORANGE);
                printf("\n\n    OUPS ! NIVEAU ECHOUE.");
                changerCouleur(COULEUR_ROUGE);
                printf("\n\n    IL VOUS RESTE %d VIES.", partie->vies);
                printf("\n    Preparez-vous a recommencer...");

                // On laisse 3 secondes pour entendre le son et lire
                Sleep(3000);

                genererNiveau(partie, partie->niveau); // On recommence le même niveau

                // On relance la musique de fond
                lancerMusique("musique.mp3");
            }
            else {
                // B) PLUS DE VIES -> VRAI GAME OVER (Dessin ASCII)
                jouerJingle("gameover.mp3");

                // C'est ici qu'on affiche le grand dessin ASCII final
                afficherDefaite();

                // On laisse 5 secondes pour bien voir l'écran et entendre la musique
                Sleep(5000);

                // Ensuite la boucle s'arrêtera car partie->vies == 0
            }
        }
    }

    // Fin de la session de jeu, on coupe tout son
    arreterMusique();
}

// === BOUCLE DE JEU (TEMPS RÉEL) ===
// Source : Assistant IA (Structure de boucle non-bloquante complexe + rafraichir 2 cases à la place de tout)
// Rôle : C'est le Moteur MUX. Il gère le timer, les inputs clavier et l'affichage simultanément.
// Entrée : La structure Partie.
// Sortie : 1 (Gagné), 0 (Perdu), -1 (Abandon).
// === BOUCLE DE JEU ===
int jouerNiveau(Partie* partie) {
    int cx = 5, cy = 5;       // Curseur actuel
    int sx = -1, sy = -1;     // Sélection
    int enCours = 1;
    int res = 0;

    // Variables pour l'optimisation d'affichage
    int oldCx = cx, oldCy = cy;

    clock_t debut = clock();
    int tempsInit = partie->temps_restant;
    int tempsLast = tempsInit;

    // 1. DESSIN INITIAL COMPLET
    afficherNiveauJeu(partie, cx, cy, sx, sy);

    while (enCours) {
        // Gestion du Timer
        clock_t now = clock();
        partie->temps_restant = tempsInit - (int)((double)(now - debut) / CLOCKS_PER_SEC);
        if (partie->temps_restant < 0) partie->temps_restant = 0;

        int aBouge = 0; // Pour savoir si on doit rafraîchir le curseur

        if (kbhit()) {
            unsigned char t = getch();

            // On sauvegarde l'ancienne position
            oldCx = cx;
            oldCy = cy;

            if (t == 224) {
                t = getch();
                switch (t) {
                    case 72: if(cy>0) { cy--; aBouge=1; } break; // Haut
                    case 80: if(cy<HAUTEUR-1) { cy++; aBouge=1; } break; // Bas
                    case 75: if(cx>0) { cx--; aBouge=1; } break; // Gauche
                    case 77: if(cx<LARGEUR-1) { cx++; aBouge=1; } break; // Droite
                }
            } else {
                switch (t) {

                    // --- MENU PAUSE (ECHAP) ---
                    case 27:
                    {
                        // On appelle ton module de pause
                        int doitQuitter = gererMenuPause(partie, &debut);

                        if (doitQuitter) {
                            enCours = 0;
                            res = -1;
                        } else {
                            // IMPORTANT : On redessine TOUT car le menu a caché le plateau
                            afficherNiveauJeu(partie, cx, cy, sx, sy);
                            // On force aBouge à 0 pour ne pas redessiner par dessus
                            aBouge = 0;
                        }
                    }
                    break;
                    // --------------------------

                    case 'z': case 'Z': if(cy>0) { cy--; aBouge=1; } break;
                    case 's': case 'S': if(cy<HAUTEUR-1) { cy++; aBouge=1; } break;
                    case 'q': case 'Q': if(cx>0) { cx--; aBouge=1; } break;
                    case 'd': case 'D': if(cx<LARGEUR-1) { cx++; aBouge=1; } break;

                    case ' ': // SELECTION
                        if (sx == -1) {
                            sx=cx; sy=cy;
                            // On met à jour juste cette case pour montrer la sélection {}
                            afficherUneCase(partie, sx, sy, cx, cy, sx, sy);
                        }
                        else {
                            if (estAdjacent(sy, sx, cy, cx)) {
                                if (permuterItems(partie, sy, sx, cy, cx)) {

                                    // 1. Explosions (Matchs)
                                    gererMatchsEtCascades(partie);

                                    // 2. VIRUS & CACTUS (Niveau 2+)
                                    if (partie->niveau >= 2) {
                                        propagerVirus(partie);
                                        appliquerGravite(partie);
                                        remplirCasesVides(partie);
                                    }

                                    // Comme le plateau a changé, on doit TOUT redessiner
                                    afficherNiveauJeu(partie, cx, cy, -1, -1);
                                    aBouge = 0; // Pas besoin de redessiner le curseur, c'est fait

                                } else {
                                    // Mouvement bloqué (Mur/Virus/Cactus)
                                    allerA(0, 35); afficherMessageTemporaire("Bloqué !"); getch();
                                    allerA(0, 35); printf("                                      "); // Efface message
                                }
                            } else {
                                allerA(0, 35); afficherMessageTemporaire("Trop loin !"); getch();
                                allerA(0, 35); printf("                                      ");
                            }

                            // Désélection : On redessine l'ancienne case sélectionnée proprement
                            int tempSx = sx, tempSy = sy;
                            sx = -1; sy = -1;
                            // Si on n'a pas tout redessiné au-dessus, on nettoie la sélection
                            if (aBouge == 0) afficherUneCase(partie, tempSx, tempSy, cx, cy, -1, -1);
                        }
                        break;
                }
            }

            // --- OPTIMISATION D'AFFICHAGE ---
            // Si on a juste bougé le curseur, on ne redessine que 2 cases
            if (aBouge) {
                afficherUneCase(partie, oldCx, oldCy, cx, cy, sx, sy); // Efface l'ancien curseur
                afficherUneCase(partie, cx, cy, cx, cy, sx, sy);       // Affiche le nouveau
            }
        }

        // Vérifications Fin de partie
        if (verifierVictoire(partie)) {
            if(!aBouge) afficherNiveauJeu(partie, cx, cy, sx, sy); Sleep(500); return 1;
        }
        if (partie->coups_restants <= 0 || partie->temps_restant <= 0) {
            if(!aBouge) afficherNiveauJeu(partie, cx, cy, sx, sy);
            partie->vies--; afficherDefaite(); getch(); return 0;
        }

        // Timer (Optimisé)
        if (enCours && !aBouge && partie->temps_restant != tempsLast) {
            tempsLast = partie->temps_restant;
            rafraichirTimerSeulement(partie);
        }

        Sleep(10);
    }
    return res;
}
