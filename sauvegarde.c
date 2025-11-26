#include <stdio.h>
#include <string.h>
#include "sauvegarde.h"

// Structure locale pour stocker le fichier en mémoire temporairement
typedef struct {
    char pseudo[50];
    int niveau;
    int vies;
} Enregistrement;

// Sauvegarde Intelligente : Met à jour ou Crée
int sauvegarderPartie(char* pseudo, int niveau, int vies) {
    Enregistrement saves[100]; // Capacité max de 100 joueurs
    int count = 0;
    int joueurTrouve = 0;

    // 1. LECTURE : On charge tout le fichier en mémoire
    FILE* fichierLecture = fopen(FICHIER_SAUVEGARDE, "r");
    if (fichierLecture != NULL) {
        while (count < 100 && fscanf(fichierLecture, "%s %d %d",
               saves[count].pseudo,
               &saves[count].niveau,
               &saves[count].vies) == 3) {

            // Si on trouve le joueur, on met à jour ses stats DIRECTEMENT
            if (strcmp(saves[count].pseudo, pseudo) == 0) {
                saves[count].niveau = niveau;
                saves[count].vies = vies;
                joueurTrouve = 1;
            }
            count++;
        }
        fclose(fichierLecture);
    }

    // 2. AJOUT : Si le joueur n'existait pas, on l'ajoute à la fin
    if (!joueurTrouve && count < 100) {
        strcpy(saves[count].pseudo, pseudo);
        saves[count].niveau = niveau;
        saves[count].vies = vies;
        count++;
    }

    // 3. ÉCRITURE : On écrase le fichier avec la liste mise à jour
    FILE* fichierEcriture = fopen(FICHIER_SAUVEGARDE, "w"); // "w" écrase tout
    if (fichierEcriture == NULL) return 0;

    for (int i = 0; i < count; i++) {
        fprintf(fichierEcriture, "%s %d %d\n", saves[i].pseudo, saves[i].niveau, saves[i].vies);
    }
    fclose(fichierEcriture);

    return 1;
}

// Chargement (Inchangé, sauf qu'il est plus fiable maintenant)
int chargerPartie(char* pseudo, int* niveau, int* vies) {
    FILE* fichier = fopen(FICHIER_SAUVEGARDE, "r");
    if (fichier == NULL) return 0;

    char pseudoLu[50];
    int niveauLu, viesLu;

    while (fscanf(fichier, "%s %d %d", pseudoLu, &niveauLu, &viesLu) == 3) {
        if (strcmp(pseudoLu, pseudo) == 0) {
            *niveau = niveauLu;
            *vies = viesLu;
            fclose(fichier);
            return 1; // Trouvé
        }
    }

    fclose(fichier);
    return 0; // Pas trouvé
}
