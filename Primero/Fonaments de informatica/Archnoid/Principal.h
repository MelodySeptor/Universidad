#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Joc.h"
#include "Configurar.h"
#include "Resultats.h"

//CONSTANTS MENU
const char JUGAR = '1';
const char CONFIGURAR = '2';
const char PUNTUACIO = '3';
const char SORTIR = '4';

//STRUCTS PRINCIPAL:
struct controlPrincipal
{
	char opcio;
	int nivell = 1;
	int punts = 0;
	char nom[MAX_LLARG_NOM];
};