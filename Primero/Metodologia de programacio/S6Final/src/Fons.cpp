#include "Fons.h"
using namespace std;

//Constructor
Fons::Fons()
{
    m_quadrats[COLOR_GROC].Create("data/Graficstetris/q1groc.png");
    m_quadrats[COLOR_TARONJA].Create("data/Graficstetris/q1taronja.png");
    m_quadrats[COLOR_ROIG].Create("data/Graficstetris/q1roig.png");
    m_quadrats[COLOR_MAGENTA].Create("data/Graficstetris/q1magenta.png");
    m_quadrats[COLOR_VERD].Create("data/Graficstetris/q1verd.png");
    m_quadrats[COLOR_BLAUCEL].Create("data/Graficstetris/q1blaucel.png");
    m_quadrats[COLOR_BLAUFOSC].Create("data/Graficstetris/q1blaufosc.png");
}

//Destructor
Fons::~Fons()
{

}

//Inicialitza el fons per jugar
void Fons::inicialitzar(const char *rutaFons)
{
    m_fons.Create(rutaFons);
    posarNegre();
    posarGris();
}

//Posa les caselles negres de la matriu
void Fons::posarNegre()
{
    for(int i=0;i<MAX_FILA;i++)
    {
        for(int j=0;j<MAX_COL;j++)
        {
            m_tauler[i][j] = COLOR_NEGRE;
        }
    }

}

//Posa les caselles grises de la matriu
void Fons::posarGris()
{
    for(int i=0;i<MAX_FILA;i++)
    {
        for(int j=0;j<MAX_COL;j++)
        {
            if((i==MAX_FILA-1)||(j==0)||(j==MAX_COL))
                m_tauler[i][j] = COLOR_GRIS;
        }
    }

}

//pinta el fons y les caselles de colors diferents
void Fons::pintaFons()
{
    m_fons.Draw(0,0);

    for (int i=0; i<MAX_FILA; i++) {
        for(int j=0; j<MAX_COL; j++) {
            int color = m_tauler[i][j];
            if (color < COLOR_NEGRE) {
                m_quadrats[color].Draw(j*MIDA_Q, i*MIDA_Q);
            }
        }
    }
}

//asigna a la matriu el que sigui
void Fons::setTauler(int fila, int columna, int color)
{
    m_tauler[fila][columna]=color;
}

//mira si es fa una linea en cualsevol posicio
bool Fons::guanyar()
{
    int a=0;
    int b=0;
    bool c=false;

	for(int i=1;i<=MAX_FILA-1;i++)
    {
        b=i;
        for(int j=1;j<=MAX_COL-1;j++)
        {
            if(m_tauler[b][j]!=COLOR_NEGRE)
            {
                a++;
            }
        }
        if(a==MAX_COL-N_COLORS_GRIS_TAUELL)
        {
            c=true;
            m_filaGuanyar = b;
            baixaTaulell();
            break;
        }
        a=0;

    }

        return c;
}

//Un cop es fa la linea baixa les posicions del taulell en 1
void Fons::baixaTaulell()
{
    for(int i=MAX_FILA;i>2;i--)
    {
        for(int j=0;j<=MAX_COL;j++)
        {
            if(i<=m_filaGuanyar)
            {
                m_tauler[i][j]=m_tauler[i-1][j];
            }
        }
    }
}

//Retorna si se ha perdut
bool Fons::perdre()
{
    return m_perd;
}

//Mira si es perd amb un bolea
bool Fons::saberiPerd(bool condic)
{
    m_perd = condic;
}

//Retorna true si la figura esta encaixada amb el fons o amb una altre figura
//Falta implementar-ho amb mascares!!! D:
bool Fons::estaEncaixada(int col, int fila, int mascara[4][4],int indexFig, int gir)
{
    if(gir==0)
    {
        switch(indexFig)
   {

    case COLOR_BLAUCEL: if((m_tauler[fila+5][col]!=COLOR_NEGRE))
    return true;
    else
        return false;
        break;

    case COLOR_GROC: if((m_tauler[fila+3][col]!=COLOR_NEGRE)||(m_tauler[fila+3][col+1]!=COLOR_NEGRE))
            {return true;}
    else
        return false;
        break;

    case COLOR_MAGENTA: if((m_tauler[fila+2][col+1]!=COLOR_NEGRE)||(m_tauler[fila+3][col]!=COLOR_NEGRE)){
        return true;
    }
    else
        return false;
        break;

    case COLOR_TARONJA: if((m_tauler[fila+3][col+1]!=COLOR_NEGRE)||(m_tauler[fila+1][col]!=COLOR_NEGRE))
    {
        return true;
    }
    else
        return false;
        break;

    case COLOR_BLAUFOSC:if((m_tauler[fila+1][col+1]!=COLOR_NEGRE)||(m_tauler[fila+3][col]!=COLOR_NEGRE))
    {
        return true;
    }
    else
        return false;
        break;

    case COLOR_VERD: if((m_tauler[fila+3][col]!=COLOR_NEGRE)||(m_tauler[fila+3][col+1]!=COLOR_NEGRE)||(m_tauler[fila+2][col+2]!=COLOR_NEGRE))
    return true;
    else
        return false;
        break;
    case COLOR_ROIG:if((m_tauler[fila+2][col]!=COLOR_NEGRE)||(m_tauler[fila+3][col+1]!=COLOR_NEGRE)||(m_tauler[fila+3][col+2]!=COLOR_NEGRE))
    {
        return true;}
    else
        return false;
        break;

    }

    }
    else
    {
        if(gir==1)
        {
             switch(indexFig)
   {

    case COLOR_BLAUCEL: if((m_tauler[fila+1][col]!=COLOR_NEGRE)||(m_tauler[fila+1][col+1]!=COLOR_NEGRE)||(m_tauler[fila+1][col+2]!=COLOR_NEGRE)||(m_tauler[fila+1][col+3]!=COLOR_NEGRE))
    {
        return true;
    }
    else
        return false;
        break;

    case COLOR_GROC: if((m_tauler[fila+3][col]!=COLOR_NEGRE)||(m_tauler[fila+3][col+1]!=COLOR_NEGRE))
            {return true;}
    else
        return false;
        break;

    case COLOR_MAGENTA: if((m_tauler[fila+2][col]!=COLOR_NEGRE)||(m_tauler[fila+2][col+1]!=COLOR_NEGRE)||(m_tauler[fila+2][col+2]!=COLOR_NEGRE)||(m_tauler[fila+3][col+1]!=COLOR_NEGRE)||(m_tauler[fila+3][col+2]!=COLOR_NEGRE)||(m_tauler[fila+3][col]!=COLOR_NEGRE))
    {
        return true;
    }
    else
        return false;
        break;

    case COLOR_TARONJA: if((m_tauler[fila+2][col]!=COLOR_NEGRE)||(m_tauler[fila+2][col+1]!=COLOR_NEGRE)||(m_tauler[fila+2][col+2]!=COLOR_NEGRE)||(m_tauler[fila+3][col+1]!=COLOR_NEGRE)||(m_tauler[fila+3][col+2]!=COLOR_NEGRE)||(m_tauler[fila+3][col]!=COLOR_NEGRE))
    {
        return true;
    }
    else
        return false;
        break;

    case COLOR_BLAUFOSC:if((m_tauler[fila+1][col]!=COLOR_NEGRE)||(m_tauler[fila+1][col+1]!=COLOR_NEGRE)||(m_tauler[fila+2][col+2]!=COLOR_NEGRE))
    {
        return true;
    }
    else
        return false;
        break;

    case COLOR_VERD: if((m_tauler[fila+2][col]!=COLOR_NEGRE)||(m_tauler[fila+3][col+1]!=COLOR_NEGRE))
    return true;
    else
        return false;
        break;
    case COLOR_ROIG:if((m_tauler[fila+2][col+1]!=COLOR_NEGRE)||(m_tauler[fila+3][col]!=COLOR_NEGRE))
    {
        return true;}
    else
        return false;
        break;

    }
        }
        else
        {
            if(gir==2)
            {
                switch(indexFig)
   {

    case COLOR_BLAUCEL: if((m_tauler[fila+5][col]!=COLOR_NEGRE))
    return true;
    else
        return false;
        break;

    case COLOR_GROC: if((m_tauler[fila+3][col]!=COLOR_NEGRE)||(m_tauler[fila+3][col+1]!=COLOR_NEGRE))
            {return true;}
    else
        return false;
        break;

    case COLOR_MAGENTA: if((m_tauler[fila+2][col]!=COLOR_NEGRE)||(m_tauler[fila+3][col+1]!=COLOR_NEGRE))
    {
        return true;
    }
    else
        return false;
        break;

    case COLOR_TARONJA: if((m_tauler[fila+3][col]!=COLOR_NEGRE)||(m_tauler[fila+3][col+1]!=COLOR_NEGRE))
    {
        return true;
    }
    else
        return false;
        break;

    case COLOR_BLAUFOSC:if((m_tauler[fila+3][col]!=COLOR_NEGRE)||(m_tauler[fila+3][col+1]!=COLOR_NEGRE))
    {
        return true;
    }
    else
        return false;
        break;

    case COLOR_VERD: if((m_tauler[fila+3][col]!=COLOR_NEGRE)||(m_tauler[fila+3][col+1]!=COLOR_NEGRE)||(m_tauler[fila+2][col+2]!=COLOR_NEGRE))
    return true;
    else
        return false;
        break;
    case COLOR_ROIG:if((m_tauler[fila+2][col]!=COLOR_NEGRE)||(m_tauler[fila+3][col+1]!=COLOR_NEGRE)||(m_tauler[fila+3][col+2]!=COLOR_NEGRE))
    {
        return true;}
    else
        return false;
        break;

    }

            }
            else
            {
                if(gir==3)
                {
                    switch(indexFig)
   {

    case COLOR_BLAUCEL: if((m_tauler[fila+1][col]!=COLOR_NEGRE)||(m_tauler[fila+1][col+1]!=COLOR_NEGRE)||(m_tauler[fila+1][col+2]!=COLOR_NEGRE)||(m_tauler[fila+1][col+3]!=COLOR_NEGRE))
    {
        return true;
    }
    else
        return false;
        break;

    case COLOR_GROC: if((m_tauler[fila+3][col]!=COLOR_NEGRE)||(m_tauler[fila+3][col+1]!=COLOR_NEGRE))
            {return true;}
    else
        return false;
        break;

    case COLOR_MAGENTA: if((m_tauler[fila+2][col]!=COLOR_NEGRE)||(m_tauler[fila+3][col+1]!=COLOR_NEGRE)||(m_tauler[fila+2][col+2]!=COLOR_NEGRE))
    {
        return true;
    }
    else
        return false;
        break;

    case COLOR_TARONJA: if((m_tauler[fila+3][col]!=COLOR_NEGRE)||(m_tauler[fila+2][col+1]!=COLOR_NEGRE)||(m_tauler[fila+2][col+2]!=COLOR_NEGRE))
    {
        return true;
    }
    else
        return false;
        break;

    case COLOR_BLAUFOSC:if((m_tauler[fila+2][col]!=COLOR_NEGRE)||(m_tauler[fila+2][col+1]!=COLOR_NEGRE)||(m_tauler[fila+2][col+2]!=COLOR_NEGRE))
    {
        return true;
    }
    else
        return false;
        break;

    case COLOR_VERD: if((m_tauler[fila+2][col]!=COLOR_NEGRE)||(m_tauler[fila+3][col+1]!=COLOR_NEGRE))
    return true;
    else
        return false;
        break;
    case COLOR_ROIG:if((m_tauler[fila+2][col+1]!=COLOR_NEGRE)||(m_tauler[fila+3][col]!=COLOR_NEGRE))
    {
        return true;}
    else
        return false;
        break;

    }
                }
            }
        }
    }
}
