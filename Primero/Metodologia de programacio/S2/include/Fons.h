#ifndef FONS_H
#define FONS_H

#include "../lib/libreria.h"
#include "iostream"


//========================================================================
// nº de píxels que ocupa un quadre dels que formen les figures del tetris
const int MIDA_Q = 26;

//========================================================================
// Inici del taulell respecte la cantonada superior esquerre
const int INICI_X = 26;
const int INICI_Y = 1;

//========================================================================
// Fi del taulell respecte la cantonada inferior dreta
const int FI_X = 312;
const int FI_Y = 547;

//========================================================================
// Mida Tauler en files i columnes
const int MAX_FILA = 22;
const int MAX_COL = 13;

//========================================================================
// Colors dels cuadrats
const int COLOR_GROC = 0;
const int COLOR_TARONJA = 1;
const int COLOR_ROIG = 2;
const int COLOR_MAGENTA = 3;
const int COLOR_VERD = 4;
const int COLOR_BLAUCEL = 5;
const int COLOR_BLAUFOSC = 6;
const int COLOR_NEGRE = 7;
const int COLOR_GRIS = 8;
const int COLOR_GROC2 = 9;
const int COLOR_TARONJA2=10;

// Maxim nombre de colors de les figures
const int MAX_COLORS = 11;

class Fons
{
    public:
        Fons();
        virtual ~Fons();
        void inicialitzar(const char*);
        void posarNegre();
        void posarGris();
        void pintaFons();
        bool guanyar();
        void setTauler(int, int, int);

    protected:
    private:
        int m_tauler [MAX_FILA][MAX_COL];
        Sprite m_quadrats[MAX_COLORS];
        Sprite m_fons;

};

#endif // FONS_H
