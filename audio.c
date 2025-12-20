#include <windows.h>
#include <stdio.h>
#include "audio.h"

static int volumeGlobal = 500; // Volume par défaut (50%)

void lancerMusique(char* nomFichier) {
    char commande[256];
    mciSendString("close bgm", NULL, 0, NULL);
    sprintf(commande, "open \"%s\" type mpegvideo alias bgm", nomFichier);
    mciSendString(commande, NULL, 0, NULL);
    mciSendString("play bgm repeat", NULL, 0, NULL); // REPEAT pour la musique de fond

    // On réapplique le volume immédiatement
    char cmdVol[100];
    sprintf(cmdVol, "setaudio bgm volume to %d", volumeGlobal);
    mciSendString(cmdVol, NULL, 0, NULL);
}

// === NOUVELLE FONCTION ===
void jouerJingle(char* nomFichier) {
    char commande[256];
    mciSendString("close bgm", NULL, 0, NULL); // On coupe la musique actuelle
    sprintf(commande, "open \"%s\" type mpegvideo alias bgm", nomFichier);
    mciSendString(commande, NULL, 0, NULL);
    mciSendString("play bgm", NULL, 0, NULL); // PAS DE REPEAT (Joue une seule fois)

    // On réapplique le volume pour que le jingle ne soit pas à fond
    char cmdVol[100];
    sprintf(cmdVol, "setaudio bgm volume to %d", volumeGlobal);
    mciSendString(cmdVol, NULL, 0, NULL);
}

void arreterMusique(void) {
    mciSendString("stop bgm", NULL, 0, NULL);
    mciSendString("close bgm", NULL, 0, NULL);
}

void changerVolumeMusique(int volume) {
    if (volume < 0) volume = 0;
    if (volume > 100) volume = 100;

    volumeGlobal = volume * 10; // Échelle 0-1000

    char commande[100];
    sprintf(commande, "setaudio bgm volume to %d", volumeGlobal);
    mciSendString(commande, NULL, 0, NULL);
}

int getVolumeActuel(void) {
    return volumeGlobal / 10;
}
