#pragma once
#include "Graphics_Console.h"
#include "Musica.h"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

//MIDES TAULELL DE JOC
const int	INICI_X = 4;
const int	INICI_Y = 5;
const int	FI_X = 36;
const int	FI_Y = 25;

//MIDES DEL MUR
const int	INICI_X_MUR = INICI_X + 3;
const int	INICI_Y_MUR = INICI_Y + 5;
const int	FI_X_MUR = FI_X - 3;
const int	FI_Y_MUR = FI_Y - 2;

//CONSTANTS CHAR
const int	MUR = 219;
const int	PILOTA = 254;//64;// arroba
const int	OFFSET = 2;
const int	FONS = 40;
const int	CORAZON = 241;//FALTA POSAR SIMBOL

//CONTROL
//Teclas
const int	ESCAPE = 27;
const int	ESCAPEANAD = 224;
const int	DRETA = 75;
const int	ESQUERRA = 77;
const int	TEST = 116;
//Joc
const int	GUANYAT = 1;
const int	PERDUT = 0;
const int	MAX_NIVELL = 4;
const int	MOURE_DRETA = -1;
const int	MOURE_ESQUERRA = 1;
const int	MOURE_ABAIX = -1;
const int	MOURE_ADALT = 1;
const int	VELOCITAT_PILOTA = 25;
const int	PINTA_ESTAT_X = (((FI_X_MUR - INICI_X_MUR) / 2) + INICI_X - 1);
const int	PINTA_ESTAT_Y = (((FI_Y_MUR - INICI_Y_MUR) / 2) + INICI_Y_MUR);

//CONSTANTS DE LA PALA
const int	PALA_AMPLADA_COMPROBA = 3;
const int	PALA_AMPLADA_DIBUIXA = 2;
const int	PALA_MIN_X_ALEATORI = INICI_X_MUR + PALA_AMPLADA_COMPROBA;
const int	PALA_MAX_X_ALEATORI = FI_X_MUR - PALA_AMPLADA_COMPROBA;

//PILOTA
const int	POS_INIC_PILOTA_Y = FI_Y_MUR - 1;

//LINEA DE JOC
const int	POS_LINEA_JOC = INICI_Y_MUR + 1;
const int	MAX_LLARG_LINEA = FI_X_MUR+1;
const int	PINTAT = 1;
const int	NO_PINTAT = 0;

//PUNTS
const int	POS_PUNTS_X = INICI_X + 2;
const int	POS_PUNTS_Y = INICI_Y - 4;

//VIDES
const int	POS_VIDES_X = INICI_X + 2;
const int	POS_VIDES_Y = INICI_Y - 2;

//NIVELL
const int	POS_NIVELL_X = FI_X - 8;
const int	POS_NIVELL_Y = INICI_Y - 4;

//FUNCIONS
int joc(int nivell);
int aleatori(int numInici, int numMax);

//STRUCTS
//Pilota
struct pilota{
	int posX = 0;
	int posY = 0;
	int dirX = 1;
	int dirY = -1;
};

//Pala
struct pala{
	int posX = 0;
};

//Control
struct control{
	char tecla = '0';
	int punts = 0;
	int vides = 3;
	int perdut = 0;
	int contador = 0;
};

//Linea Joc
struct lineaJoc{
	int arrayMur[MAX_LLARG_LINEA];
	int color = (aleatori(BLUE, WHITE));
};