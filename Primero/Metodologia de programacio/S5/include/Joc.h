
#include <conio.h>      /* getch */
#include <stdio.h>      /* printf */
#include <time.h>       /* time */
#include "FigTetris.h"

//===================================================================================
// Codis tecles
const int  TECLA_ESC = 27;
const int  TECLA_DRETA = 77;
const int  TECLA_ESQUERRA = 75;
const int  TECLA_ABAIX = 80;
const int  TECLA_ADALT = 444;
const int   TECLA_ESPAI = 394;

const int TEMPS_PERDUA = 5;

const int MAX_NIVELL = 5;

void pintarPeca(int x, int y, int obj);

int llegirEvent();
int aleatori(int min, int max);
int llargPeca(int obj);

int  limitiDretX(int obj);

void tractarEvent(int tecla, FigTetris& fig, Fons& fons);

void pintarMeta(int meta[]);
int guanyar(int meta[]);
void crearFigTetris(FigTetris*);

int joc(int nivell);

/*----- END --------------*/

