#ifndef AUDIO_H
#define AUDIO_H

// Initialise et lance la musique en boucle
void lancerMusique(char* nomFichier);

// Lance un jingle une seule fois (Victoire/Défaite)
void jouerJingle(char* nomFichier);

// Arrête la musique
void arreterMusique(void);

// Change le volume (de 0 à 100)
void changerVolumeMusique(int volume);

// Retourne le volume actuel
int getVolumeActuel(void);

#endif // AUDIO_H
