#include "Resultats.h"

//Mostra el "menu" dels resultats
void mostraMenu() {
	system("cls");
	printf("------MILLORS PUNTUACIONS------\n\n");
	printf("NOM\t\t\tPUNTS\n\n");
}

//Inserta un jugador en la posicio especifica que es diu
void insertaJugadorEnPosicio(Jugador llistaJugadors[], char nom[], int punts, int index) {
	strcpy_s(llistaJugadors[index].nom, nom);
	llistaJugadors[index].punts = punts;
}

//Mira si hi han posicions lliures per insertar i retorna la posicio
int afegirEspaiBlanc(int &index, Jugador llistaJugadors[]) {
	int i = 0;
	while ((index == -1) && (i != MAX_JUGADORS)) {
		if (!(strcmp(llistaJugadors[i].nom, "NONE")))
			index = i;
		else
			i++;
	}
	return index;
}

//Mira si es pot afegir un jugador per la seva puntuacio
int afegirMillorPuntuacio(int &index, Jugador llistaJugadors[],int punts) {
	int j = 0;
	while ((index == -1) && (j != MAX_JUGADORS)) {
		if (llistaJugadors[j].punts < punts)
			index = j;
		else
			j++;
	}
	return index;
}

//Inserta un nou jugador a la llista comprobant la posicio on ho ha de fer
void insertaNouJugador(Jugador llistaJugadors[], int punts, char nom[]) {
	int index = -1;
	if (afegirEspaiBlanc(index, llistaJugadors) != NO_ESPAI)
		insertaJugadorEnPosicio(llistaJugadors, nom, punts, index);
	else if (afegirMillorPuntuacio(index, llistaJugadors, punts) != NO_ESPAI) {
		insertaJugadorEnPosicio(llistaJugadors, nom, punts, index);
	}
}

//Retorna el numero de jugadors que hi ha en la llista
int contaJugadorsLlista(Jugador llistaJugadors[]) {
	int maxJugadors = 0;
	for (int z = 0;z < MAX_JUGADORS;z++) {
		if (strcmp(llistaJugadors[z].nom, "NONE") != 0)
			maxJugadors++;
	}
	return maxJugadors;
}

//Intercambia dos elements en les posicions x y
void ordenarElements(Jugador llistaJugadors[],int x, int y) {
	char auxC[MAX_LLARG_NOM];
	int auxP;

	strcpy_s(auxC, llistaJugadors[x].nom);
	auxP = llistaJugadors[x].punts;
	llistaJugadors[x] = llistaJugadors[y];
	strcpy_s(llistaJugadors[y].nom, auxC);
	llistaJugadors[y].punts = auxP;
}

//Ordena la llista de Jugadors, unicament la part on hi han jugadors
void ordenarLlista(Jugador llistaJugadors[]) {
	int x,y,maxJugadors = contaJugadorsLlista(llistaJugadors);
	for (x = 0;x < maxJugadors;x++) {
		for (y = 0;y < maxJugadors;y++) {
			if (llistaJugadors[x].punts > llistaJugadors[y].punts) {
				ordenarElements(llistaJugadors, x, y);
			}
		}
	}
}

//Inserta una nova persona a la llista, de manera ordenada
void insertaNouOrdenat(Jugador llistaJugadors[], int punts, char nom[]) {
	insertaNouJugador(llistaJugadors,punts,nom);
	ordenarLlista(llistaJugadors);
}

//Mostra la llista de jugadors per pantalla
void mostraLlista(Jugador llistaJugadors[]) {
	for (int i = 0;i < MAX_JUGADORS;i++) {
		printf("%s\t\t\t%d\n", llistaJugadors[i].nom,llistaJugadors[i].punts);
	}
}

//Funcio principal dels resultats
void resultats(Jugador llistaJugadros[]) {
	pararMusica();
	musicaResultatsON();
	mostraMenu();
	mostraLlista(llistaJugadros);
	char pausa = _getch();
	pararMusica();
}