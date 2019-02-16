#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "Musica.h"

const int MAX_JUGADORS = 5;
const int MAX_LLARG_NOM = 16;
const int NO_ESPAI = -1;

struct Jugador
{
	char nom[MAX_LLARG_NOM] = "NONE";
	int punts = 0;
};

void resultats(Jugador llistaJugadros[]);
void insertaNouOrdenat(Jugador llistaJugadors[], int punts, char nom[]);