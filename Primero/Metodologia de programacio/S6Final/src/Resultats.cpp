#include "Resultats.h"

//Construcor
Resultats::Resultats()
{
    m_digits[0].Create("data/numeros/numero0000.png");
    m_digits[1].Create("data/numeros/numero0001.png");
    m_digits[2].Create("data/numeros/numero0002.png");
    m_digits[3].Create("data/numeros/numero0003.png");
    m_digits[4].Create("data/numeros/numero0004.png");
    m_digits[5].Create("data/numeros/numero0005.png");
    m_digits[6].Create("data/numeros/numero0006.png");
    m_digits[7].Create("data/numeros/numero0007.png");
    m_digits[8].Create("data/numeros/numero0008.png");
    m_digits[9].Create("data/numeros/numero0009.png");
}

//Destructor
Resultats::~Resultats()
{

}

//Inicialitza tot el necesari
void Resultats::inicialitzar(const char* rutaResultats)
{
   m_resultats.Create(rutaResultats);
}

//Pinta per pantalla totes les cosas
void Resultats::pintaResultats(int nivell, int punts, int vides)
{
    m_resultats.Draw(POS_RESX,POS_RESY);
    escriuNumero(nivell,POS_NIV_RESX,POS_NIV_RESY,PAS_DIGIT_X);
    escriuNumero(punts,POS_PUNTS_RESX,POS_PUNTS_RESY,PAS_DIGIT_X);
    escriuNumero(vides,POS_VIDES_X,POS_VIDES_Y,PAS_DIGIT_X);
}

//escriu digit, no te misteri
void Resultats::escriuDigit(int n, int posX, int posY)
{
   m_digits[n].Draw(posX,posY);
}

//escriu numero (ya venia feta)
void Resultats::escriuNumero(int n,int posX,int posY,int pasDigit)
{
    int divisor = 100;
    int posXActual = posX;
    int nActual =n;
    bool primerDigit = true;

    while (divisor > 0)
    {
        int d = nActual / divisor;
        nActual = nActual % divisor;
        divisor = divisor / 10;

        if ( (d > 0) || !primerDigit || (divisor == 0) )
        {
            escriuDigit( d , posXActual, posY);
            primerDigit = false;
        }

        posXActual += pasDigit;
    }
}
