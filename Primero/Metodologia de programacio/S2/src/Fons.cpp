#include "Fons.h"
using namespace std;

Fons::Fons()
{
    // Constructor. No s'ha de modificar.
    // Crea els gràfics que s'utilitzaran per dibuixar els quadrats de colors al tauler a mesura que les figures vagin arribant a baix de tot
    m_quadrats[COLOR_GROC].Create("data/Graficstetris/q1groc.png");
    m_quadrats[COLOR_TARONJA].Create("data/Graficstetris/q1taronja.png");
    m_quadrats[COLOR_ROIG].Create("data/Graficstetris/q1roig.png");
    m_quadrats[COLOR_MAGENTA].Create("data/Graficstetris/q1magenta.png");
    m_quadrats[COLOR_VERD].Create("data/Graficstetris/q1verd.png");
    m_quadrats[COLOR_BLAUCEL].Create("data/Graficstetris/q1blaucel.png");
    m_quadrats[COLOR_BLAUFOSC].Create("data/Graficstetris/q1blaufosc.png");
    m_quadrats[COLOR_NEGRE].Create("data/Graficstetris/q1groc.png");
    m_quadrats[COLOR_GRIS].Create("data/Graficstetris/q1groc.png");
    m_quadrats[COLOR_GROC2].Create("data/Graficstetris/q1groc.png");
    m_quadrats[COLOR_TARONJA2].Create("data/Graficstetris/q1taronja.png");
}

Fons::~Fons()
{
    // Destructor. No s'ha de modificar
}

void Fons::inicialitzar(const char *rutaFons)
{
    // TODO
    // Heu de crear l'Sprite amb el dibuix del fons del tauler
    // També heu d'inicialitzar totes les posicions de la matriu m_tauler  a color negre, excepte la primera i ultima columna
    // i la última fila que s'han d'inicialitzar a gris. D'aquesta manera marquem que tot el tauler està buit. Per fer-ho podeu utilitzar
    // els mètodes posarNegre() i posarGris()
    m_fons.Create(rutaFons);
    posarNegre();
    posarGris();
}
void Fons::posarNegre()
{
    // TODO
    // Heu d'inicialitzar totes les posicions interiors (que no són límits) de la matriu m_tauler a negre
    for(int i=0;i<=MAX_FILA;i++)
    {
        for(int j=0;j<=MAX_COL;j++)
        {
            if((i!=MAX_FILA)||(j!=0)||(j=!MAX_COL))
                m_tauler[i][j] = COLOR_NEGRE;
        }
    }

}

void Fons::posarGris()
{
    // TODO
    // Heu d'inicialitzar primera i ultima columnes de la matriu m_tauler a gris
    // Heu d'inicialitzar la última fila de la matriu m_tauler a gris
    for(int i=0;i<=MAX_FILA;i++)
    {
        for(int j=0;j<=MAX_COL;j++)
        {
            if((i==MAX_FILA)||(j==0)||(j==MAX_COL))
                m_tauler[i][j] = COLOR_GRIS;
        }
    }

}

void Fons::pintaFons()
{
    // TODO:
    // Heu de pintar tots els quadres del fons del tauler que que no són negres i que per tant corresponen a figures que ja s'han col·locat al tauler.
    // De moment, tots els quadres de color (no negres) estaran a l'úlitima línia del tauler
    // Recoreu que els quares grisos del tauler ja estan pintats a la imatge del fons i no els heu de tornar a dibuixar.
    m_fons.Draw(0,0);
    int indexFig;
    for(int i=1;i<=MAX_FILA-1;i++)
    {
        for(int j=1;j<=MAX_COL-1;j++)
        {
           if(m_tauler[i][j]!=COLOR_NEGRE)
           {
               indexFig=m_tauler[i][j];
                 if(indexFig==0)
                    {
                        indexFig=COLOR_GROC2;
                    }
                if(indexFig==1)
                    {
                        indexFig=COLOR_TARONJA2;
                    }
                m_quadrats[indexFig].Draw(((i-1)*MIDA_Q),FI_Y-MIDA_Q);
           }
        }
    }
}

void Fons::setTauler(int fila, int columna, int color)
{
    // TODO
    // Heu de modificar el valor de color de la posició fila, columna del tauler (valor de la matriu m_tauler) amb el color que es passa com a paràmetre.
    m_tauler[fila][columna]=color;
}


bool Fons::guanyar()
{
    int a=0;
	// TODO
	// Heu de retornar cert si la última línia del tauler que no està gris està tota pintada de colors
	// i fals si hi ha algun quadre a negre.
	for(int i=1;i<=MAX_FILA-1;i++)
    {
        for(int j=1;j<=MAX_COL-1;j++)
        {
            if(m_tauler[i][j]!=COLOR_NEGRE)
            {
                a++;
            }
        }
    }
    if(a==MAX_COL-2)
        return true;
    else
        return false;
}
