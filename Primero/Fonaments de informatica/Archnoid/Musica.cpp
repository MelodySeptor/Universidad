#include "Musica.h"

//Musica del Menu ON
void musicaMenuON() {
	PlaySound(TEXT("Menu.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

//Musica del Joc ON
void musicaJocON() {
	PlaySound(TEXT("Joc.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

//Musica dels Resultats ON
void musicaResultatsON() {
	PlaySound(TEXT("Resultats.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

//Musica OFF
void pararMusica() {
	PlaySound(NULL, 0, 0);
}