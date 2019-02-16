
#include "Joc.h"
#include "lib/libreria.h"
#include <cstdlib>
void triarPeca(int aleatori)
{

     // "data/Graficstetris/palblaucel2.png"
    // "data/Graficstetris/pblaufosc4.png"
    // "data/Graficstetris/tmagenta2.png"
    // "data/Graficstetris/q4groc1.png"
}
void escriuDigit(int n, int posX, int posY)
{
    Sprite uno("data/numeros/numero0001.png");
    Sprite dos("data/numeros/numero0002.png");
    Sprite tres("data/numeros/numero0003.png");
    Sprite quatre("data/numeros/numero0004.png");
    Sprite cinc("data/numeros/numero0005.png");
    Sprite sis("data/numeros/numero0006.png");
    Sprite siete("data/numeros/numero0007.png");
    Sprite vuit("data/numeros/numero0008.png");
    Sprite nou("data/numeros/numero0009.png");
    Sprite zero("data/numeros/numero0000.png");

    switch(n)
    {
        case 1: {
                    uno.Draw(posX,posY);
                    break;
        }
        case 2: {
                    dos.Draw(posX,posY);
                    break;
        }
        case 3: {
                    tres.Draw(posX,posY);
                    break;
        }
        case 4: {
                    quatre.Draw(posX,posY);
                    break;
        }
        case 5: {
                    cinc.Draw(posX,posY);
                    break;
        }
        case 6: {
                    sis.Draw(posX,posY);
                    break;
        }
        case 7: {
                    siete.Draw(posX,posY);
                    break;
        }
        case 8: {
                    vuit.Draw(posX,posY);
                    break;
        }
        case 9: {
                    nou.Draw(posX,posY);
                    break;
        }
        case 0: {
                    zero.Draw(posX,posY);
                    break;
        }
    }
}
void escriuNumero(int n,int posX,int posY,int pasDigit)
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

        if ( (d > 0) || !primerDigit )
        {
            escriuDigit( d , posXActual, posY);
            primerDigit = false;
        }

        posXActual += pasDigit;
    }
}
int llegirEvent()
{
    // ***
    // Aquesta funció ha de capturar si s'ha pressionat alguna de les tecles del joc utilizant
    // la funció de la llibreria gràfica que permet detectar si s'ha pressionat alguna tecla.
    // La funció ha de retornar el codi de la tecla que s'ha pressionat
    // El codi de cada tecla està definit al fitxer joc.h
    // En el codi del projecte TestGrafics trobareu un exemple de com utilitzar les funcions de
    // la llibreria gràfica per capturar el teclat

}

// Funció que retorna un valor aleatori entre min i max
// No cal modificar-la
int aleatori(int min, int max)
{
	int aleatori = rand() % (max - min + 1) + min; // (FI_Y - INICI_Y - 4) + (INICI_Y+3)
	return aleatori;
}


// Funció que retorna el nº de columnes que ocupa una peça
// No cal modificar-la
int llargPeca(int obj)
{
    int llarg = 0;
    switch (obj)
    {
        case I:
            llarg = 4;
            break;
        case O:
            llarg = 2;
            break;
        case T:
        case L:
            llarg = 3;
            break;
    }
    return llarg;
}

int altPeca(int obj)
{
    // ***
    // Aquesta funció és una nova funció que no estava al projecte de FI
    // Ha de retornar el número de files que ocupa una peça de forma similar a com
    // la funció llargPeca retorna el número de columnes de la peça
}



int limitiDretX(int obj)
{
    // ***
    // Aquesta funció retorna la úlitma coordenada per la dreta on es pot col·locar una peça sense que surti
    // del taulell. Aquí us donem el codi de la funció que correspon al projecte de FI
    // Heu de modificar aquest codi que us donem perquè tingui en compte l'amplada en píxels de cada peça
    // La funció llargPeca retorna el nº de columnes que ocupa una peça. S'ha de tenir en compte que cada
    // columna ocupa una amplada en píxels equivalent al valor de la constant MIDA_Q
    return (FI_X - llargPeca(obj));
}


// Aquesta funció inicialitza l'array que permet controlar quines posicions de l'última fila estan ocupades
// Hi ha una posició de l'array per cada columna del taulell
// Inicialment totes les posicions estan a 1. A mesura que es van ocupant es van posant a 0
// No cal modificar-la
void inicialitzarMeta(int meta[])
{
	for(int i = 0; i < COL_X; i++)
	    meta[i] = 1;
}



void arribadaMeta(int obj, int x, int meta[])
{
    // ***
    // Aquesta funció actualitza l'array que controla les posiccions de l'última fila ocupades
    // Cal modificar només el càlcul de la columna (pos) a partir de la coordinada x de la peça
    // La resta de la funció no cal modificar-la
    // Aquí us donem el codi del projecte de FI on cada columna ocupava només 1 posició
    // Ara cal tenir en compte que cada columna ocupa una amplada en píxels equivalent a MIDA_Q
	int pos = x - INICI_X - 1;

	for(int i = pos; i <= pos + 1; i++)
    {
        switch (obj)
        {
            case I:
                meta[i] = 0;
			    meta[i + 2] = 0;
                break;
            case O:
                meta[i] = 0;
                break;
            case T:
            case L:
                meta[i]   = 0;
                meta[i + 1] = 0;
                break;
        }
    }
}


void mourePeca(int& x, int& y, int dirX, int dirY, int& obj, int meta[])
{
    // ***
    // Aquesta funció mou una peça segons els valors dels paràmetres dirX i dirY
    // Si la peça arriba al final del taulell es torna a generar una nova peça que apareix a
    // la part de dalt del taulell.
    // Cal modificar tot el que té a veure amb el càlcul i control de les coordinades de la peça
    // per tenir en compte que cada columna i fila ocupen una amplada i alçada en píxels equivalent a MIDA_Q
    // Aquí us donem el codi del projecte de FI on cada columna i fila ocupaven només 1 posició
	if( y < (FI_Y - 1))
    {
        x += dirX;
        y += dirY;
    }
    else
    {
		arribadaMeta(obj, x, meta);

		obj  = aleatori(I, L);
        x = aleatori(INICI_X + 1,  limitiDretX(obj));
        y = INICI_Y;
    }
}


void tractarEvent(int tecla, int& x, int& y, int& obj, int meta[])
{
    // ***
    // Aquesta funció decideix quin moviment s'ha de fer a la peça en funció de la tecla que s'hagi pressionat
    // Abans de fer el moviment de la peça es comprova que no superi els límits del taulell
    // Cal modificar tot el que té a veure amb el control de les coordinades de la peça
    // per tenir en compte que cada columna i fila ocupen una amplada i alçada en píxels equivalent a MIDA_Q
    // Aquí us donem el codi del projecte de FI on cada columna i fila ocupaven només 1 posició
	switch(tecla)
	{
		case TECLA_ESQUERRA:
			if ( x > (INICI_X + 1) )
				mourePeca(x, y, -1, 0, obj, meta);
			break;
		case TECLA_DRETA:
			if ( x < limitiDretX(obj))
				mourePeca(x, y, 1, 0, obj, meta);
			break;
		case TECLA_ABAIX:
			if ( y < (FI_Y - 2))
				mourePeca(x, y, 0, 2, obj, meta);
			break;
		default: break;
	}
}

// Funció que retorna un 0 si totes les posicions de l'última fila estan ocpuades.
// En cas contrari, retorna un valor diferent de 0
// No cal modificar-la
int guanyar(int meta[])
{
	int sum = 0;

	for(int i = 0; i < COL_X; i++)
		sum += meta[i];

	return sum;
}


void pintaMeta(int meta[])
{
    // ***
    // Aquesta és una nova funció que haurà de pintar un quadrat vermell (gràfic "data/Graficstetris/q1roig.png")
    // a totes les columnes de l'úlitma fila que estiguin ocupades (posicions de l'array meta amb valor igual a 0

}


int joc(int nivell)
{
    // ***
    // En aquest punt hauren de cridar a les funcions d'inicialització de la llibreria gràfica
    // igual que està fet al projecte TestGrafics
    Game joc;
    // Inicialitzacions necessàries
	joc.Init();
    Sprite tetris[4];

	int peca, pecaX, pecaY;
    int tecla = 0;
    int pasBaixa = MIDA_Q;
    int meta[COL_X];
    int metaAconseguida;
    char direccio='0';

	int velocitatJoc = 5000;
	int contVPeca;

	int vides = 3;
	int punts = 0;
	int diffT = 0;
	time_t now;
	srand((unsigned)time(NULL));

    // ***
    // En aquest punt haureu de crear els gràfics de les 4 peces, el gràfic del fons del taulel i el gràfic
    // que permet mostrar els resultats. Per les peces necessitareu 4 variables de tipus Sprite, una per cada peça
    // Preneu com a referència el codi de creació dels gràfics al projecte TestGrafics
    // Els gràfics que heu d'utilitzar per les peces, el fons i el resultat són:
    // "data/Graficstetris/palblaucel2.png"
    // "data/Graficstetris/pblaufosc4.png"
    // "data/Graficstetris/tmagenta2.png"
    // "data/Graficstetris/q4groc1.png"
    // "data/GraficsTetris/fons.png"
    // "data/GraficsTetris/Resultats.png"

    // També haureu de mostrar la pantalla gràfica cridant a la funció Video_ShowWindow() igual que al projecte TestGrafics

    tetris[0].Create("data/Graficstetris/tmagenta2.png");
    tetris[1].Create("data/Graficstetris/q4groc1.png");
    tetris[2].Create("data/Graficstetris/pblaufosc4.png");
    tetris[3].Create("data/Graficstetris/palblaucel2.png");
    Sprite fons("data/GraficsTetris/fons.png");
    Sprite resultats("data/GraficsTetris/Resultats.png");
    joc.Video_ShowWindow();

	do
    {

        // Inicialització de la posició de la peça
        peca  = aleatori(I, L);

        // ***
        // En aquest punt heu de modificar la inicialització de la coordinada X de la peça perquè
        // es correspongui amb el valor en píxels d'alguna columna vàlida del taulell
        // Podeu prendre com a referència la inicialització de la posició de la peça que es fa al projecte TestGrafics
        int posicioTetrisX = (INICI_X) + ( ( rand() % ( ( (FI_X - INICI_X - tetris[peca].getScaleX()) / MIDA_Q ) + 1 ) ) * MIDA_Q );
		int posicioTetrisY = INICI_Y;

        metaAconseguida = 1;
        inicialitzarMeta(meta);
        contVPeca = velocitatJoc / nivell;
        now = time(NULL);

        // ***
        // En aquest punt haureu de dibuixar el fons, les peces, el fons dels resultats, la puntuació i el nivell actual
        // Per dibuixar les peces tingueu en compte que haureu de dibuixar un gràfic diferent segons el valor
        // de la peça actual que determina la variable peca
        // Podeu prendre com a referència el codi que dibuixa fons, resultats i peça al projecte TestGrafics
        // Podeu copiar i utilitzar les funcions del projecte TestGrafics que s'utilitzen per escriure números
        // Finalment heu de cridar a la funció VideoUpdate() per refrescar la pantalla de forma similar a com
        // es fa al projecte TestGrafics
            fons.Draw(0, 0);
			tetris[peca].Draw(posicioTetrisX, posicioTetrisY);

            //Pinta resultats
            resultats.Draw(POS_RESX,POS_RESY);
            escriuNumero(nivell, POS_NIV_RESX, POS_NIV_RESY, PAS_DIGIT_X);
            escriuNumero(punts, POS_CENT_RESX, POS_NUM_RESY, PAS_DIGIT_X);

			// Actualitza la pantalla
            joc.VideoUpdate();
            bool figuraFinal =false;
        do
        {
            // ***
            // En aquest punt haureu de cridar a la funció ProcessEvents de forma similar a com es fa al projecte
            // TestGrafics. Després es crida a les versions modificades de llegirEvent i tractarEvent (no cal modificar
            // aquestes crides)
           joc.ProcessEvents(); // Captura els events que s'han produit en el darrer cicle
			if (Keyboard_GetKeyTrg(KEYBOARD_LEFT))
			{
				// Si la posició de la figura és més gran que el límit esquerra + el desplaçament de cada moviment
				if ( posicioTetrisX >= (INICI_X + MIDA_Q))
				{
					// Movem figura a l'esquerra
					posicioTetrisX -= MIDA_Q;
				}
			} else if (Keyboard_GetKeyTrg(KEYBOARD_RIGHT))
			{
			    // Si la posició de la figura + el tamany en horizontal de la figura és més petita que el límit dret - el desplaçament de cada moviment
				if ( (posicioTetrisX + tetris[peca].getScaleX()) <= (FI_X - MIDA_Q) )
				{
					// Movem la figura a la dreta
					posicioTetrisX += MIDA_Q;
				}
			}
			else if (Keyboard_GetKeyTrg(KEYBOARD_DOWN))
			{
			    // Si la posició de la figura + el tamany en vertical de la figura és més petita que el límit inferior - el desplaçament de cada moviment
				if ( (posicioTetrisY + tetris[peca].getScaleY()) <= (FI_Y - pasBaixa) )
				{
					// Movem la figura a la dreta
					posicioTetrisY += pasBaixa;
				}
				if (posicioTetrisY + tetris[peca].getScaleY() >= FI_Y )
                {
                    figuraFinal = true;
                }
			}
			else if (Keyboard_GetKeyTrg(KEYBOARD_SPACE))
			{
			    // Si la posició de la figura no és el final
				if (posicioTetrisY + tetris[peca].getScaleY() <= FI_Y )
				{
					// Posem la figura al fons
					posicioTetrisY = FI_Y - tetris[peca].getScaleY();
					figuraFinal = true;
				}
			}
            // ***
            // En aquest punt haureu de tornar a dibuixar el fons, les peces, el fons dels resultats, la puntuació
            // i el nivell actual exactament igual que heu fet més amunt
            // A més a més, aquí haureu de dibuixar també l'ocupació de l'última fila cridant a la funció pintarMeta

            fons.Draw(0, 0);
			tetris[peca].Draw(posicioTetrisX, posicioTetrisY);

            //Pinta resultats
            resultats.Draw(POS_RESX,POS_RESY);
            escriuNumero(nivell, POS_NIV_RESX, POS_NIV_RESY, PAS_DIGIT_X);
            escriuNumero(punts, POS_CENT_RESX, POS_NUM_RESY, PAS_DIGIT_X);

			// Actualitza la pantalla
            joc.VideoUpdate();
            diffT = difftime(time(NULL),  now);

            if(diffT > (TEMPS_PERDUA / nivell))
            {
                metaAconseguida = 0;
                vides--;
            }


            if(figuraFinal)
            {
                metaAconseguida = 0;
                punts += nivell;
                nivell++;
            }



        }while((!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE)) && metaAconseguida);

	}while((nivell<4) && (vides>0) && (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE)));


	return punts;
}
