#include "FigTetris.h"

FigTetris::FigTetris()
{
    // Constructor. No s'ha de modificar
}

FigTetris::~FigTetris()
{
    // Destructor. No s'ha de modificar
}

void FigTetris::setPosX(int posX)
{
    // TODO
    // Heu de modificar el valor de l'atribut m_posX (posició x de la figura) amb el valor posX que es passa com a paràmetre
    m_posX=posX;
}

void FigTetris::setPosY(int posY)
{
    // TODO
    // Heu de modificar el valor de l'atribut m_posY (posició y de la figura) amb el valor posY que es passa com a paràmetre
    m_posY=posY;
}

void FigTetris::draw()
{
    // TODO
    // Heu e dibuixar el gràfic de la figura del tetris a la posicio m_posX, m_posY
    m_figura.Draw(m_posX,m_posY);
}

void FigTetris::create(int indexFig)
{
    // TODO
    // Heu de crear una de les figures del tetris en funció de l'índex que es passa com a paràmetre
    // A continuació teniu el gràfic que heu d'utilitzar per cada possible valor de indexFig
    // I: ("data/Graficstetris/palblaucel1.png")
    // O:("data/Graficstetris/q4groc1.png")
    // T:("data/Graficstetris/tmagenta2.png")
    // L:("data/Graficstetris/ltaronja2.png")
    // P:("data/Graficstetris/pblaufosc4.png")
    // S:("data/Graficstetris/sverd1.png")
    // Z:("data/Graficstetris/zroig1.png")
    // Per cada figura, a més a més de
    //crear el gràfic heu d'inicialitzar la
    //resta dels atributs de la classe (amplada, alçada, index i color)
    switch(indexFig)
    {
    case O:
        {
            m_figura.Create("data/Graficstetris/q4groc1.png");
           m_amplada =m_figura.getScaleX();
           m_alcada = m_figura.getScaleY();
           m_indexFig = O;
           m_color = COLOR_GROC;
           break;
        }
        case L:
        {
             m_figura.Create("data/Graficstetris/ltaronja2.png");
           m_amplada =m_figura.getScaleX();
           m_alcada = m_figura.getScaleY();
           m_indexFig = L;
           m_color = COLOR_TARONJA;
           break;
        }
        case Z:
        {
            m_figura.Create("data/Graficstetris/zroig1.png");
           m_amplada =m_figura.getScaleX();
           m_alcada = m_figura.getScaleY();
           m_indexFig = Z;
           m_color = COLOR_ROIG;
           break;
        }
        case T:
        {
            m_figura.Create("data/Graficstetris/tmagenta2.png");
           m_amplada =m_figura.getScaleX();
           m_alcada = m_figura.getScaleY();
           m_indexFig = T;
           m_color = COLOR_MAGENTA;
           break;
        }
        case S:
        {
            m_figura.Create("data/Graficstetris/sverd1.png");
           m_amplada =m_figura.getScaleX();
           m_alcada = m_figura.getScaleY();
           m_indexFig = S;
           m_color = COLOR_VERD;
           break;
        }
        case I:
        {
            m_figura.Create("data/Graficstetris/palblaucel1.png");
           m_amplada =m_figura.getScaleX();
           m_alcada = m_figura.getScaleY();
           m_indexFig = I;
           m_color = COLOR_BLAUCEL;
           break;
        }
        case P:
        {
            m_figura.Create("data/Graficstetris/pblaufosc4.png");
           m_amplada =m_figura.getScaleX();
           m_alcada = m_figura.getScaleY();
           m_indexFig = P;
           m_color = COLOR_BLAUFOSC;
           break;
        }
    }
}

int FigTetris::amplada()
{
    // TODO
    // Retorna l'amplada de la figura
    return m_amplada;
}

int FigTetris::alcada()
{
    // TODO
    // Retorna l'alçada de la figura
    return m_alcada;
}

bool FigTetris::moureFig(int dirX, int dirY, Fons& fons)
{
    // TODO:
    // Heu d'analitzar si es pot fer el moviment indicat a dirX i dirY en funció de l'estat del fons i de la posició actual de la figura.
    // Si el moviment és possible, haure de modificar com correspongui el valor dels atributs m_posX i m_posY per actualitzar la posició
    // de la figura d'acord al moviment indicat. La funció ha de retornar true si la figura ha arribat a l'última línia del tauler

    // Els valors de dirX i dirX que indiquen el moviment poden ser de moment:
    // -1, 0: moviment a l'esquerra. Aqui sempre retornem fals.
    // 1, 0: moviment a la dreta. Aqui sempre retornem fals.
    // 0, 1: moviment a baix. Aqui a més hem de veure si ja hem arribat a baix de tot. Si hem arribat retornarem true,
    //       i actualitzarem la última línia del tauler del fons amb els quadres del color de la figura actual.
    // 0, 2: moviment a baix de dues posicions. Aqui a més hem de veure si ja hem arribat a baix de tot. Si hem arribat retornarem true,
    //       i actualitzarem la última línia del tauler del fons amb els quadres del color de la figura actual.
    if((dirX==1)&&(dirY==0))
    {
        if(m_posX+MIDA_Q<=FI_X-m_amplada)
        {
            m_posX=dirX*MIDA_Q+m_posX;
            return false;
        }
    }

    if((dirX==-1)&&(dirY==0))
    {
        if((m_posX)>=(INICI_X+MIDA_Q))
            {
            m_posX = m_posX+(dirX*MIDA_Q);
            return false;
            }
    }
    if((dirX==0)&&(dirY==1))
    {
        if(m_posY==FI_Y-m_alcada)
        {
            figuraEncaixada(fons);
            return true;
        }
        else
        {
            m_posY = m_posY+MIDA_Q;
            return false;
        }
    }
    if((dirX==0)&&(dirY==2))
    {
        if(m_posY==FI_Y-m_alcada)
        {
            figuraEncaixada(fons);
            return true;
        }
        else
        {
            m_posY = m_posY+2*MIDA_Q;
            return false;
        }
    }
    /*if((dirX==0)&&(dirY==-1))
    {
        m_posY = FI_Y-m_alcada;
        figuraEncaixada(fons);
        return true;
    }*/

}

void FigTetris::figuraEncaixada(Fons& fons)
{
	// TODO:
	// Aquest mètode s'ha de cridar quan la figura arriba a baix de tot.
	// Modifica els quadres corresponents a l'amplada de la figura actual a
	//les posicions de la última línia del tauler el fons amb els colors de la figura actual

    switch (m_indexFig)
	{
	    case I:{fons.setTauler(m_posX/MIDA_Q,m_posY/MIDA_Q,m_color);break;}
	    case O:{fons.setTauler(m_posX/MIDA_Q,m_posY/MIDA_Q,m_color);
	    fons.setTauler((m_posX/MIDA_Q)+1,m_posY/MIDA_Q,m_color);break;}
	    case L:{fons.setTauler(m_posX/MIDA_Q,m_posY/MIDA_Q,m_color);
	     fons.setTauler((m_posX/MIDA_Q)+1,m_posY/MIDA_Q,m_color);
	      fons.setTauler((m_posX/MIDA_Q)+2,m_posY/MIDA_Q,m_color);break;}
        case S:{ fons.setTauler((m_posX/MIDA_Q),m_posY/MIDA_Q,m_color);
         fons.setTauler((m_posX/MIDA_Q)+1,m_posY/MIDA_Q,m_color);break;}
        case Z:{ fons.setTauler((m_posX/MIDA_Q)+1,m_posY/MIDA_Q,m_color);
         fons.setTauler((m_posX/MIDA_Q)+2,m_posY/MIDA_Q,m_color);break;}
        case P: {fons.setTauler(m_posX/MIDA_Q,m_posY/MIDA_Q,m_color);
	     fons.setTauler((m_posX/MIDA_Q)+1,m_posY/MIDA_Q,m_color);
	      fons.setTauler((m_posX/MIDA_Q)+2,m_posY/MIDA_Q,m_color);break;}
        case T:{fons.setTauler(m_posX/MIDA_Q,m_posY/MIDA_Q,m_color);
	     fons.setTauler((m_posX/MIDA_Q)+1,m_posY/MIDA_Q,m_color);
	      fons.setTauler((m_posX/MIDA_Q)+2,m_posY/MIDA_Q,m_color);break;}
	}
}
