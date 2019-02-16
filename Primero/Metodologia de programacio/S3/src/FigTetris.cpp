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
    // Heu de modificar el valor de l'atribut m_posX (posici� x de la figura) amb el valor posX que es passa com a par�metre
    m_posX=posX;
}

void FigTetris::setPosY(int posY)
{
    // TODO
    // Heu de modificar el valor de l'atribut m_posY (posici� y de la figura) amb el valor posY que es passa com a par�metre
    m_posY=posY;
}

void FigTetris::draw()
{
    // TODO
    // Heu e dibuixar el gr�fic de la figura del tetris a la posicio m_posX, m_posY
    m_figura.Draw(m_posX,m_posY);
}

void FigTetris::create(int indexFig)
{
    // TODO
    // Heu de crear una de les figures del tetris en funci� de l'�ndex que es passa com a par�metre
    // A continuaci� teniu el gr�fic que heu d'utilitzar per cada possible valor de indexFig
    // I: ("data/Graficstetris/palblaucel1.png")
    // O:("data/Graficstetris/q4groc1.png")
    // T:("data/Graficstetris/tmagenta2.png")
    // L:("data/Graficstetris/ltaronja2.png")
    // P:("data/Graficstetris/pblaufosc4.png")
    // S:("data/Graficstetris/sverd1.png")
    // Z:("data/Graficstetris/zroig1.png")
    // Per cada figura, a m�s a m�s de
    //crear el gr�fic heu d'inicialitzar la
    //resta dels atributs de la classe (amplada, al�ada, index i color)

    int aux[4][4];
    //Solo ponemos los 1 que puedan colisionar, lo otro lo dejamos a 0 aunque pertenezca a la figura

    switch(indexFig)
    {
    case O:
        {
            m_figura.Create("data/Graficstetris/q4groc1.png");
           m_amplada =m_figura.getScaleX();
           m_alcada = m_figura.getScaleY();
           m_indexFig = O;
           m_color = COLOR_GROC;

           int aux[4][4] = {
            {1,1,0,0},
            {0,0,0,0},
            {0,0,0,0},
            {0,0,0,0}
           };
           break;
        }
        case L:
        {
             m_figura.Create("data/Graficstetris/ltaronja2.png");
           m_amplada =m_figura.getScaleX();
           m_alcada = m_figura.getScaleY();
           m_indexFig = L;
           m_color = COLOR_TARONJA;

            int aux[4][4] = {
            {1,1,1,0},
            {0,0,0,0},
            {0,0,0,0},
            {0,0,0,0}
           };
           break;
        }
        case Z:
        {
            m_figura.Create("data/Graficstetris/zroig1.png");
           m_amplada =m_figura.getScaleX();
           m_alcada = m_figura.getScaleY();
           m_indexFig = Z;
           m_color = COLOR_ROIG;

           int aux[4][4] = {
            {0,1,1,0},
            {1,0,0,0},
            {0,0,0,0},
            {0,0,0,0}
           };
           break;
        }
        case T:
        {
            m_figura.Create("data/Graficstetris/tmagenta2.png");
           m_amplada =m_figura.getScaleX();
           m_alcada = m_figura.getScaleY();
           m_indexFig = T;
           m_color = COLOR_MAGENTA;

           int aux[4][4] = {
            {1,1,1,0},
            {0,0,0,0},
            {0,0,0,0},
            {0,0,0,0}
           };
           break;
        }
        case S:
        {
            m_figura.Create("data/Graficstetris/sverd1.png");
           m_amplada =m_figura.getScaleX();
           m_alcada = m_figura.getScaleY();
           m_indexFig = S;
           m_color = COLOR_VERD;

           int aux[4][4] = {
            {1,1,0,0},
            {0,0,1,0},
            {0,0,0,0},
            {0,0,0,0}
           };
           break;
        }
        case I:
        {
            m_figura.Create("data/Graficstetris/palblaucel1.png");
           m_amplada =m_figura.getScaleX();
           m_alcada = m_figura.getScaleY();
           m_indexFig = I;
           m_color = COLOR_BLAUCEL;

           int aux[4][4] = {
            {1,0,0,0},
            {0,0,0,0},
            {0,0,0,0},
            {0,0,0,0}
           };
           break;
        }
        case P:
        {
            m_figura.Create("data/Graficstetris/pblaufosc4.png");
           m_amplada =m_figura.getScaleX();
           m_alcada = m_figura.getScaleY();
           m_indexFig = P;
           m_color = COLOR_BLAUFOSC;

           int aux[4][4] = {
            {1,1,1,0},
            {0,0,0,0},
            {0,0,0,0},
            {0,0,0,0}
           };

           break;
        }
    }
    memcpy(m_mascara, aux, sizeof(m_mascara));
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
    // Retorna l'al�ada de la figura
    return m_alcada;
}

bool FigTetris::moureFig(int dirX, int dirY, Fons& fons)
{
    // TODO:
    // Heu d'analitzar si es pot fer el moviment indicat a dirX i dirY en funci� de l'estat del fons i de la posici� actual de la figura.
    // Si el moviment �s possible, haure de modificar com correspongui el valor dels atributs m_posX i m_posY per actualitzar la posici�
    // de la figura d'acord al moviment indicat. La funci� ha de retornar true si la figura ha arribat a l'�ltima l�nia del tauler

    // Els valors de dirX i dirY que indiquen el moviment poden ser de moment:
    // -1, 0: moviment a l'esquerra. Aqui sempre retornem fals.
    // 1, 0: moviment a la dreta. Aqui sempre retornem fals.
    // 0, 1: moviment a baix. Aqui a m�s hem de veure si ja hem arribat a baix de tot. Si hem arribat retornarem true,
    //       i actualitzarem la �ltima l�nia del tauler del fons amb els quadres del color de la figura actual.
    // 0, 2: moviment a baix de dues posicions. Aqui a m�s hem de veure si ja hem arribat a baix de tot. Si hem arribat retornarem true,
    //       i actualitzarem la �ltima l�nia del tauler del fons amb els quadres del color de la figura actual.

    //Si la figura es la I passem un 2 com a par�metre per evitar que la figura baixi m�s del compte
    bool encaixada;
    if(m_indexFig == I){
        encaixada = fons.estaEncaixada(m_posX/MIDA_Q, m_posY/MIDA_Q, m_mascara, 2);
    } else {
        encaixada = fons.estaEncaixada(m_posX/MIDA_Q, m_posY/MIDA_Q, m_mascara, 0);
    }

    if((dirX==1)&&(dirY==0))
    {
        if((m_posX +(dirX*MIDA_Q)) <= FI_X-m_amplada)
        {
            if(!encaixada){
            m_posX=dirX*MIDA_Q+m_posX;
            return false;}
            else
                return false;
        }
    }

    if((dirX==-1)&&(dirY==0))
    {
        if((m_posX+(dirX*MIDA_Q))>=(INICI_X))
            {
            if(!encaixada){
            m_posX = m_posX+(dirX*MIDA_Q);
            return false;}
            else
                return false;
            }
    }
    if((dirX==0)&&(dirY==1))
    {
        if(m_posY >= FI_Y-MIDA_Q - this->alcada())
        {
            figuraEncaixada(fons);
            return true;
        }

        if (encaixada){
                if(m_posY<=INICI_X)
                {
                    fons.saberiPerd(true);
                }
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
        if(m_posY+2*MIDA_Q>=FI_Y)
        {
            figuraEncaixada(fons);
            return true;
        }
        if (encaixada) {
            figuraEncaixada(fons);
            return true;
        }
        else
        {
            m_posY = m_posY+2*MIDA_Q;
            return false;
        }
    }
}

void FigTetris::figuraEncaixada(Fons& fons)
{
	// TODO:
	// Aquest m�tode s'ha de cridar quan la figura arriba a baix de tot.
	// Modifica els quadres corresponents a l'amplada de la figura actual a
	// les posicions de la �ltima l�nia del tauler el fons amb els colors de la figura actual

	int i;

    switch(m_indexFig){
    case I:
        for(i=0; i<this->alcada()/MIDA_Q; i++) {
            fons.setTauler(m_posY/MIDA_Q+i+1, m_posX/MIDA_Q, m_color);
        }
        break;
    case O:
        for(i=0; i<(this->amplada()/MIDA_Q); i++) {
            fons.setTauler(m_posY/MIDA_Q +2, m_posX/MIDA_Q + i, m_color);
            fons.setTauler(m_posY/MIDA_Q+1, m_posX/MIDA_Q + i, m_color);
        }
        break;
    case T:
        for(i=0; i<this->amplada()/MIDA_Q; i++){
            fons.setTauler(m_posY/MIDA_Q +2, m_posX/MIDA_Q + i, m_color);
        }
        fons.setTauler(m_posY/MIDA_Q+1, m_posX/MIDA_Q + 1, m_color);
        break;
    case L:
        for(i=0; i<this->amplada()/MIDA_Q; i++){
            fons.setTauler(m_posY/MIDA_Q +2, m_posX/MIDA_Q + i, m_color);
        }
        fons.setTauler(m_posY/MIDA_Q+1, m_posX/MIDA_Q + 2, m_color);
        break;
    case P:
        for(i=0; i<this->amplada()/MIDA_Q; i++){
            fons.setTauler(m_posY/MIDA_Q +2, m_posX/MIDA_Q + i, m_color);
        }
        fons.setTauler(m_posY/MIDA_Q+1, m_posX/MIDA_Q, m_color);
        break;
    case S:
        fons.setTauler(m_posY/MIDA_Q+2, m_posX/MIDA_Q, m_color);
        fons.setTauler(m_posY/MIDA_Q+1, m_posX/MIDA_Q + 1, m_color);
        fons.setTauler(m_posY/MIDA_Q+2, m_posX/MIDA_Q +1, m_color);
        fons.setTauler(m_posY/MIDA_Q+1, m_posX/MIDA_Q + 2, m_color);
        break;
    case Z:
        for(i=0; i<this->amplada()/MIDA_Q-1; i++){
            fons.setTauler(m_posY/MIDA_Q +2, m_posX/MIDA_Q + i+ 1, m_color);
            fons.setTauler(m_posY/MIDA_Q+1, m_posX/MIDA_Q + i , m_color);
        }
        break;

    }
}
