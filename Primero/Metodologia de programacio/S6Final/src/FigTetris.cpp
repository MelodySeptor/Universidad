#include "FigTetris.h"
using namespace std;

//Constructor
FigTetris::FigTetris()
{
    m_gir=0;
}

//Destructor
FigTetris::~FigTetris()
{

}

//Asigna la X
void FigTetris::setPosX(int posX)
{
    m_posX=posX;
}

//Assigna la Y
void FigTetris::setPosY(int posY)
{
    m_posY=posY;
}

//Dibuixa en x,y
void FigTetris::draw()
{
    switch(m_gir)
    {
    case 0:{m_figura.Draw(m_posX,m_posY);break;}
    case 1:{m_figura2.Draw(m_posX,m_posY);break;}
    case 2:{m_figura3.Draw(m_posX,m_posY);break;}
    case 3:{m_figura4.Draw(m_posX,m_posY); break;}
    }

}

//Crea cada figura amb els sprites corresponents de cada gir
void FigTetris::create(int indexFig)
{
    int aux[4][4];

    switch(indexFig)
    {
    case O:
        {
            m_figura.Create("data/Graficstetris/q4groc1.png");
            m_figura2.Create("data/Graficstetris/q4groc1.png");
            m_figura3.Create("data/Graficstetris/q4groc1.png");
            m_figura4.Create("data/Graficstetris/q4groc1.png");
            m_amplada =m_figura.getScaleX();
            m_alcada = m_figura.getScaleY();
            m_indexFig = O;
            m_color = COLOR_GROC;

           int aux[4][4] = {
            {1,1,0,0},
            {1,1,0,0},
            {0,0,0,0},
            {0,0,0,0}
           };
           break;
        }
        case L:
        {
             m_figura.Create("data/Graficstetris/ltaronja1.png");
             m_figura2.Create("data/Graficstetris/ltaronja2.png");
             m_figura3.Create("data/Graficstetris/ltaronja3.png");
             m_figura4.Create("data/Graficstetris/ltaronja4.png");

           m_amplada =m_figura.getScaleX();
           m_alcada = m_figura.getScaleY()-MIDA_Q;
           m_indexFig = L;
           m_color = COLOR_TARONJA;

            int aux[4][4] = {
            {0,0,1,0},
            {1,1,1,0},
            {0,0,0,0},
            {0,0,0,0}
           };
           break;
        }
        case Z:
        {
            m_figura.Create("data/Graficstetris/zroig1.png");
            m_figura2.Create("data/Graficstetris/zroig2.png");
            m_figura3.Create("data/Graficstetris/zroig1.png");
            m_figura4.Create("data/Graficstetris/zroig2.png");
           m_amplada =m_figura.getScaleX();
           m_alcada = m_figura.getScaleY();
           m_indexFig = Z;
           m_color = COLOR_ROIG;

           int aux[4][4] = {
            {0,1,1,0},
            {1,1,0,0},
            {0,0,0,0},
            {0,0,0,0}
           };
           break;
        }
        case T:
        {
            m_figura.Create("data/Graficstetris/tmagenta1.png");
            m_figura2.Create("data/Graficstetris/tmagenta2.png");
            m_figura3.Create("data/Graficstetris/tmagenta3.png");
            m_figura4.Create("data/Graficstetris/tmagenta4.png");
           m_amplada =m_figura.getScaleX();
           m_alcada = m_figura.getScaleY()-MIDA_Q;
           m_indexFig = T;
           m_color = COLOR_MAGENTA;

           int aux[4][4] = {
            {0,1,0,0},
            {1,1,1,0},
            {0,0,0,0},
            {0,0,0,0}
           };
           break;
        }
        case S:
        {
            m_figura.Create("data/Graficstetris/sverd1.png");
            m_figura2.Create("data/Graficstetris/sverd2.png");
            m_figura3.Create("data/Graficstetris/sverd1.png");
            m_figura4.Create("data/Graficstetris/sverd2.png");
           m_amplada =m_figura.getScaleX();
           m_alcada = m_figura.getScaleY();
           m_indexFig = S;
           m_color = COLOR_VERD;

           int aux[4][4] = {
            {1,1,0,0},
            {0,1,1,0},
            {0,0,0,0},
            {0,0,0,0}
           };
           break;
        }
        case I:
        {
            m_figura.Create("data/Graficstetris/palblaucel1.png");
            m_figura2.Create("data/Graficstetris/palblaucel2.png");
            m_figura3.Create("data/Graficstetris/palblaucel1.png");
            m_figura4.Create("data/Graficstetris/palblaucel2.png");
           m_amplada =m_figura.getScaleX();
           m_alcada = m_figura.getScaleY();
           m_indexFig = I;
           m_color = COLOR_BLAUCEL;

           int aux[4][4] = {
            {1,0,0,0},
            {1,0,0,0},
            {1,0,0,0},
            {1,0,0,0}
           };
           break;
        }
        case P:
        {
            m_figura.Create("data/Graficstetris/pblaufosc1.png");
            m_figura2.Create("data/Graficstetris/pblaufosc2.png");
            m_figura3.Create("data/Graficstetris/pblaufosc3.png");
            m_figura4.Create("data/Graficstetris/pblaufosc4.png");
           m_amplada =m_figura.getScaleX();
           m_alcada = m_figura.getScaleY()-MIDA_Q;
           m_indexFig = P;
           m_color = COLOR_BLAUFOSC;

           int aux[4][4] = {
            {1,0,0,0},
            {1,1,1,0},
            {0,0,0,0},
            {0,0,0,0}
           };

           break;
        }
    }
    memcpy(m_mascara, aux, sizeof(m_mascara));
}

//retorna la amplada de la figura
int FigTetris::amplada()
{
    return m_amplada;
}

//Retorna la alçada
int FigTetris::alcada()
{
    return m_alcada;
}

//Ens diu si ha arribat abaix de tot returnant true
//Mou la figura cap a cualsevol costar y mira si esta encaixada amb una altre o el fons
//retorna false si no arriba avall o esta encaixada
bool FigTetris::moureFig(int dirX, int dirY, Fons& fons)
{
    bool encaixada=fons.estaEncaixada(m_posX/MIDA_Q, m_posY/MIDA_Q, m_mascara,m_indexFig,m_gir);

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
        if(m_posY >= FI_Y-MIDA_Q - m_alcada)
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

//girar la figura
void FigTetris::girarFig(Fons& fons)
{
    if((m_gir==0)&&(m_posX+m_figura2.getScaleX()<=FI_X))
    {
        m_gir++;

        if((m_indexFig==I)||(m_indexFig==P)||(m_indexFig==S)||(m_indexFig==Z))
        {
            m_alcada = m_figura2.getScaleY()-MIDA_Q;
        }
        else
            m_alcada = m_figura2.getScaleY();
        m_amplada =m_figura2.getScaleX();

    }
    else
    {
        if((m_gir==1)&&(m_posX+m_figura3.getScaleX()<=FI_X))
        {
            m_gir++;
            if((m_indexFig==T)||(m_indexFig==L)||(m_indexFig==P))
            {
                m_alcada = m_figura3.getScaleY()-MIDA_Q;
            }
            else
                m_alcada = m_figura3.getScaleY();
            m_amplada =m_figura3.getScaleX();

        }
        else
        {
            if((m_gir==2)&&(m_posX+m_figura4.getScaleX()<=FI_X))
            {
                m_gir++;
                if((m_indexFig==O)||(m_indexFig==T)||(m_indexFig==L))
                {
                    m_alcada = m_figura4.getScaleY();
                }
                else
                {
                   m_alcada = m_figura4.getScaleY()-MIDA_Q;
                }
                m_amplada =m_figura4.getScaleX();

            }
            else
            {
                if((m_posX+m_figura.getScaleX()<=FI_X)){
                m_gir=0;
                m_amplada =m_figura.getScaleX();

                if((m_indexFig==T)||(m_indexFig==L)||(m_indexFig==P))
                {
                    m_alcada = m_figura.getScaleY()-MIDA_Q;
                }
                else
                   m_alcada = m_figura.getScaleY();

            }}
        }
    }
}

//Falta fer-ho per mascara
//Pasa al fons on ha quedat la figura
void FigTetris::figuraEncaixada(Fons& fons)
{
    int i;
if(m_gir==0)
{
    switch(m_indexFig)
    {
    case I:
        for(i=0; i<m_alcada/MIDA_Q; i++) {
            fons.setTauler(m_posY/MIDA_Q+i+1, m_posX/MIDA_Q, m_color);
        }
        break;
    case O:
        for(i=0; i<(m_amplada/MIDA_Q); i++) {
            fons.setTauler(m_posY/MIDA_Q +2, m_posX/MIDA_Q + i, m_color);
            fons.setTauler(m_posY/MIDA_Q+1, m_posX/MIDA_Q + i, m_color);
        }
        break;
    case T:
        for(i=0; i<m_alcada/MIDA_Q; i++){
            fons.setTauler(m_posY/MIDA_Q +i, m_posX/MIDA_Q, m_color);
        }
        fons.setTauler(m_posY/MIDA_Q +2, m_posX/MIDA_Q, m_color);
        fons.setTauler(m_posY/MIDA_Q+1, m_posX/MIDA_Q + 1, m_color);
        break;
    case L:
        for(i=0; i<m_alcada/MIDA_Q; i++){
            fons.setTauler(m_posY/MIDA_Q +i, m_posX/MIDA_Q + 1, m_color);
        }
        fons.setTauler(m_posY/MIDA_Q, m_posX/MIDA_Q , m_color);
        fons.setTauler(m_posY/MIDA_Q +2, m_posX/MIDA_Q + 1, m_color);
        break;
    case P:
        for(i=0; i<m_alcada/MIDA_Q; i++){
            fons.setTauler(m_posY/MIDA_Q +i, m_posX/MIDA_Q, m_color);
        }
        fons.setTauler(m_posY/MIDA_Q, m_posX/MIDA_Q+1, m_color);
        fons.setTauler(m_posY/MIDA_Q +2, m_posX/MIDA_Q, m_color);
        break;
    case S:
        fons.setTauler(m_posY/MIDA_Q+2, m_posX/MIDA_Q, m_color);
        fons.setTauler(m_posY/MIDA_Q+1, m_posX/MIDA_Q + 1, m_color);
        fons.setTauler(m_posY/MIDA_Q+2, m_posX/MIDA_Q +1, m_color);
        fons.setTauler(m_posY/MIDA_Q+1, m_posX/MIDA_Q + 2, m_color);
        break;
    case Z:
        for(i=0; i<m_amplada/MIDA_Q-1; i++){
            fons.setTauler(m_posY/MIDA_Q +2, m_posX/MIDA_Q + i+ 1, m_color);
            fons.setTauler(m_posY/MIDA_Q+1, m_posX/MIDA_Q + i , m_color);
        }
        break;

    }
}
else
{
    if(m_gir==1)
    {
 switch(m_indexFig)
    {
    case I:
        for(i=0; i<m_amplada/MIDA_Q; i++) {
            fons.setTauler(m_posY/MIDA_Q, m_posX/MIDA_Q+i, m_color);
        }
        break;
    case O:
        for(i=0; i<(m_amplada/MIDA_Q); i++) {
            fons.setTauler(m_posY/MIDA_Q +2, m_posX/MIDA_Q + i, m_color);
            fons.setTauler(m_posY/MIDA_Q+1, m_posX/MIDA_Q + i, m_color);
        }
        break;
    case T:
        for(i=0; i<m_amplada/MIDA_Q; i++){
            fons.setTauler(m_posY/MIDA_Q +2, m_posX/MIDA_Q + i, m_color);
        }
        fons.setTauler(m_posY/MIDA_Q +2, m_posX/MIDA_Q + 2, m_color);
        fons.setTauler(m_posY/MIDA_Q+1, m_posX/MIDA_Q + 1, m_color);
        break;
    case L:
        for(i=0; i<m_amplada/MIDA_Q; i++){
            fons.setTauler(m_posY/MIDA_Q +2, m_posX/MIDA_Q + i, m_color);
        }
        fons.setTauler(m_posY/MIDA_Q+1, m_posX/MIDA_Q + 2, m_color);
        break;
    case P:
        for(i=0; i<m_amplada/MIDA_Q; i++){
            fons.setTauler(m_posY/MIDA_Q , m_posX/MIDA_Q+i, m_color);
        }
        fons.setTauler(m_posY/MIDA_Q+1, m_posX/MIDA_Q+2, m_color);
        break;
    case S:
        fons.setTauler(m_posY/MIDA_Q, m_posX/MIDA_Q, m_color);
        fons.setTauler(m_posY/MIDA_Q+1, m_posX/MIDA_Q, m_color);
        fons.setTauler(m_posY/MIDA_Q+1, m_posX/MIDA_Q +1, m_color);
        fons.setTauler(m_posY/MIDA_Q+2, m_posX/MIDA_Q + 1, m_color);
        break;
    case Z:
        fons.setTauler(m_posY/MIDA_Q, m_posX/MIDA_Q+1, m_color);
        fons.setTauler(m_posY/MIDA_Q+1, m_posX/MIDA_Q+1, m_color);
        fons.setTauler(m_posY/MIDA_Q+1, m_posX/MIDA_Q, m_color);
        fons.setTauler(m_posY/MIDA_Q+2, m_posX/MIDA_Q, m_color);
        break;

    }
    }
    else
    {
        if(m_gir==2)
        {
        switch(m_indexFig)
    {
    case I:
        for(i=0; i<m_alcada/MIDA_Q; i++) {
            fons.setTauler(m_posY/MIDA_Q+i+1, m_posX/MIDA_Q, m_color);
        }
        break;
    case O:
        for(i=0; i<(m_amplada/MIDA_Q); i++) {
            fons.setTauler(m_posY/MIDA_Q +2, m_posX/MIDA_Q + i, m_color);
            fons.setTauler(m_posY/MIDA_Q+1, m_posX/MIDA_Q + i, m_color);
        }
        break;
    case T:
        for(i=0; i<m_alcada/MIDA_Q; i++){
            fons.setTauler(m_posY/MIDA_Q +i, m_posX/MIDA_Q + 1, m_color);
        }
        fons.setTauler(m_posY/MIDA_Q +2, m_posX/MIDA_Q + 1, m_color);
        fons.setTauler(m_posY/MIDA_Q+1, m_posX/MIDA_Q, m_color);
        break;
    case L:
        for(i=0; i<m_alcada/MIDA_Q; i++){
            fons.setTauler(m_posY/MIDA_Q +i, m_posX/MIDA_Q, m_color);
        }
        fons.setTauler(m_posY/MIDA_Q +2, m_posX/MIDA_Q, m_color);
        fons.setTauler(m_posY/MIDA_Q+2, m_posX/MIDA_Q + 1, m_color);
        break;
    case P:
        for(i=0; i<m_alcada/MIDA_Q; i++){
            fons.setTauler(m_posY/MIDA_Q+i , m_posX/MIDA_Q+1, m_color);
        }
        fons.setTauler(m_posY/MIDA_Q+2 , m_posX/MIDA_Q+1, m_color);
        fons.setTauler(m_posY/MIDA_Q+2, m_posX/MIDA_Q, m_color);
        break;
    case S:
         fons.setTauler(m_posY/MIDA_Q+2, m_posX/MIDA_Q, m_color);
        fons.setTauler(m_posY/MIDA_Q+1, m_posX/MIDA_Q + 1, m_color);
        fons.setTauler(m_posY/MIDA_Q+2, m_posX/MIDA_Q +1, m_color);
        fons.setTauler(m_posY/MIDA_Q+1, m_posX/MIDA_Q + 2, m_color);
        break;
    case Z:
         for(i=0; i<m_amplada/MIDA_Q-1; i++){
            fons.setTauler(m_posY/MIDA_Q +2, m_posX/MIDA_Q + i+ 1, m_color);
            fons.setTauler(m_posY/MIDA_Q+1, m_posX/MIDA_Q + i , m_color);
        }
        break;

    }
        }
        else
        {
            if(m_gir==3)
            {
        switch(m_indexFig)
    {
    case I:
        for(i=0; i<m_amplada/MIDA_Q; i++) {
            fons.setTauler(m_posY/MIDA_Q, m_posX/MIDA_Q+i, m_color);
        }
        break;
    case O:
        for(i=0; i<(m_amplada/MIDA_Q); i++) {
            fons.setTauler(m_posY/MIDA_Q +2, m_posX/MIDA_Q + i, m_color);
            fons.setTauler(m_posY/MIDA_Q+1, m_posX/MIDA_Q + i, m_color);
        }
        break;
    case T:
        for(i=0; i<m_amplada/MIDA_Q; i++){
            fons.setTauler(m_posY/MIDA_Q +1, m_posX/MIDA_Q + i, m_color);
        }
        fons.setTauler(m_posY/MIDA_Q+2, m_posX/MIDA_Q + 1, m_color);
        break;
    case L:
        for(i=0; i<m_amplada/MIDA_Q; i++){
            fons.setTauler(m_posY/MIDA_Q +1, m_posX/MIDA_Q + i, m_color);
        }
        fons.setTauler(m_posY/MIDA_Q+2, m_posX/MIDA_Q, m_color);
        break;
    case P:
       for(i=0; i<m_amplada/MIDA_Q; i++){
            fons.setTauler(m_posY/MIDA_Q +1, m_posX/MIDA_Q + i, m_color);
        }
        fons.setTauler(m_posY/MIDA_Q, m_posX/MIDA_Q, m_color);
        break;
    case S:
        fons.setTauler(m_posY/MIDA_Q, m_posX/MIDA_Q, m_color);
        fons.setTauler(m_posY/MIDA_Q+1, m_posX/MIDA_Q, m_color);
        fons.setTauler(m_posY/MIDA_Q+1, m_posX/MIDA_Q +1, m_color);
        fons.setTauler(m_posY/MIDA_Q+2, m_posX/MIDA_Q + 1, m_color);
        break;
    case Z:
        fons.setTauler(m_posY/MIDA_Q, m_posX/MIDA_Q+1, m_color);
        fons.setTauler(m_posY/MIDA_Q+1, m_posX/MIDA_Q+1, m_color);
        fons.setTauler(m_posY/MIDA_Q+1, m_posX/MIDA_Q, m_color);
        fons.setTauler(m_posY/MIDA_Q+2, m_posX/MIDA_Q, m_color);
        break;

    }
            }
        }
    }
}

}

//Cuant arriba abaix reinicia el gir de la figura a la inicial
void FigTetris::reiniciarGir()
{
    m_gir =0;
    m_amplada =m_figura.getScaleX();
    if((m_indexFig==T)||(m_indexFig==L)||(m_indexFig==P))
        {
            m_alcada = m_figura.getScaleY()-MIDA_Q;
        }
    else
        m_alcada = m_figura.getScaleY();
}
