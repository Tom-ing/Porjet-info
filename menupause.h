#ifndef MENUPAUSE_H
#define MENUPAUSE_H

#include <time.h>        // Pour gérer le temps (clock_t)
#include "structures.h"  // Pour connaître la structure Partie

// Rôle : Gère tout le menu pause (affichage, choix, sauvegarde, calcul du temps perdu)
// Entrées : 
//   - partie : pour sauvegarder
//   - debutNiveau : pointeur vers le chrono du main pour le "geler"
// Sortie : 
//   - Retourne 1 si le joueur veut QUITTER le niveau
//   - Retourne 0 si le joueur veut REPRENDRE
// Source : Aide IA (Modularisation)
int gererMenuPause(Partie* partie, clock_t* debutNiveau);

#endif // MENUPAUSE_H
