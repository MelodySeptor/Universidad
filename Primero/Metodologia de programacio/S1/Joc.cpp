
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
    // Aquesta funci� ha de capturar si s'ha pressionat alguna de les tecles del joc utilizant
    // la funci� de la llibreria gr�fica que permet detectar si s'ha pressionat alguna tecla.
    // La funci� ha de retornar el codi de la tecla que s'ha pressionat
    // El codi de cada tecla est� definit al fitxer joc.h
    // En el codi del projecte TestGrafics trobareu un exemple de com utilitzar les funcions de
    // la llibreria gr�fica per capturar el teclat

}

// Funci� que retorna un valor aleatori entre min i max
// No cal modificar-la
int aleatori(int min, int max)
{
	int aleatori = rand() % (max - min + 1) + min; // (FI_Y - INICI_Y - 4) + (INICI_Y+3)
	return aleatori;
}


// Funci� que retorna el n� de columnes que ocupa una pe�a
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
    // Aquesta funci� �s una nova funci� que no estava al projecte de FI
    // Ha de retornar el n�mero de files que ocupa una pe�a de forma similar a com
    // la funci� llargPeca retorna el n�mero de columnes de la pe�a
}



int limitiDretX(int obj)
{
    // ***
    // Aquesta funci� retorna la �litma coordenada per la dreta on es pot col�locar una pe�a sense que surti
    // del taulell. Aqu� us donem el codi de la funci� que correspon al projecte de FI
    // Heu de modificar aquest codi que us donem perqu� tingui en compte l'amplada en p�xels de cada pe�a
    // La funci� llargPeca retorna el n� de columnes que ocupa una pe�a. S'ha de tenir en compte que cada
    // columna ocupa una amplada en p�xels equivalent al valor de la constant MIDA_Q
    return (FI_X - llargPeca(obj));
}


// Aquesta funci� inicialitza l'array que permet controlar quines posicions de l'�ltima fila estan ocupades
// Hi ha una posici� de l'array per cada columna del taulell
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
    // Aquesta funci� actualitza l'array que controla les posiccions de l'�ltima fila ocupades
    // Cal modificar nom�s el c�lcul de la columna (pos) a partir de la coordinada x de la pe�a
    // La resta de la funci� no cal modificar-la
    // Aqu� us donem el codi del projecte de FI on cada columna ocupava nom�s 1 posici�
    // Ara cal tenir en compte que cada columna ocupa una amplada en p�xels equivalent a MIDA_Q
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
    // Aquesta funci� mou una pe�a segons els valors dels par�metres dirX i dirY
    // Si la pe�a arriba al final del taulell es torna a generar una nova pe�a que apareix a
    // la part de dalt del taulell.
    // Cal modificar tot el que t� a veure amb el c�lcul i control de les coordinades de la pe�a
    // per tenir en compte que cada columna i fila ocupen una amplada i al�ada en p�xels equivalent a MIDA_Q
    // Aqu� us donem el codi del projecte de FI on cada columna i fila ocupaven nom�s 1 posici�
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
    // Aquesta funci� decideix quin moviment s'ha de fer a la pe�a en funci� de la tecla que s'hagi pressionat
    // Abans de fer el moviment de la pe�a es comprova que no superi els l�mits del taulell
    // Cal modificar tot el que t� a veure amb el control de les coordinades de la pe�a
    // per tenir en compte que cada columna i fila ocupen una amplada i al�ada en p�xels equivalent a MIDA_Q
    // Aqu� us donem el codi del projecte de FI on cada columna i fila ocupaven nom�s 1 posici�
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

// Funci� que retorna un 0 si totes les posicions de l'�ltima fila estan ocpuades.
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
    // Aquesta �s una nova funci� que haur� de pintar un quadrat vermell (gr�fic "data/Graficstetris/q1roig.png")
    // a totes les columnes de l'�litma fila que estiguin ocupades (posicions de l'array meta amb valor igual a 0

}


int joc(int nivell)
{
    // ***
    // En aquest punt hauren de cridar a les funcions d'inicialitzaci� de la llibreria gr�fica
    // igual que est� fet al projecte TestGrafics
    Game joc;
    // Inicialitzacions necess�ries
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
    // En aquest punt haureu de crear els gr�fics de les 4 peces, el gr�fic del fons del taulel i el gr�fic
    // que permet mostrar els resultats. Per les peces necessitareu 4 variables de tipus Sprite, una per cada pe�a
    // Preneu com a refer�ncia el codi de creaci� dels gr�fics al projecte TestGrafics
    // Els gr�fics que heu d'utilitzar per les peces, el fons i el resultat s�n:
    // "data/Graficstetris/palblaucel2.png"
    // "data/Graficstetris/pblaufosc4.png"
    // "data/Graficstetris/tmagenta2.png"
    // "data/Graficstetris/q4groc1.png"
    // "data/GraficsTetris/fons.png"
    // "data/GraficsTetris/Resultats.png"

    // Tamb� haureu de mostrar la pantalla gr�fica cridant a la funci� Video_ShowWindow() igual que al projecte TestGrafics

    tetris[0].Create("data/Graficstetris/tmagenta2.png");
    tetris[1].Create("data/Graficstetris/q4groc1.png");
    tetris[2].Create("data/Graficstetris/pblaufosc4.png");
    tetris[3].Create("data/Graficstetris/palblaucel2.png");
    Sprite fons("data/GraficsTetris/fons.png");
    Sprite resultats("data/GraficsTetris/Resultats.png");
    joc.Video_ShowWindow();

	do
    {

        // Inicialitzaci� de la posici� de la pe�a
        peca  = aleatori(I, L);

        // ***
        // En aquest punt heu de modificar la inicialitzaci� de la coordinada X de la pe�a perqu�
        // es correspongui amb el valor en p�xels d'alguna columna v�lida del taulell
        // Podeu prendre com a refer�ncia la inicialitzaci� de la posici� de la pe�a que es fa al projecte TestGrafics
        int posicioTetrisX = (INICI_X) + ( ( rand() % ( ( (FI_X - INICI_X - tetris[peca].getScaleX()) / MIDA_Q ) + 1 ) ) * MIDA_Q );
		int posicioTetrisY = INICI_Y;

        metaAconseguida = 1;
        inicialitzarMeta(meta);
        contVPeca = velocitatJoc / nivell;
        now = time(NULL);

        // ***
        // En aquest punt haureu de dibuixar el fons, les peces, el fons dels resultats, la puntuaci� i el nivell actual
        // Per dibuixar les peces tingueu en compte que haureu de dibuixar un gr�fic diferent segons el valor
        // de la pe�a actual que determina la variable peca
        // Podeu prendre com a refer�ncia el codi que dibuixa fons, resultats i pe�a al projecte TestGrafics
        // Podeu copiar i utilitzar les funcions del projecte TestGrafics que s'utilitzen per escriure n�meros
        // Finalment heu de cridar a la funci� VideoUpdate() per refrescar la pantalla de forma similar a com
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
            // En aquest punt haureu de cridar a la funci� ProcessEvents de forma similar a com es fa al projecte
            // TestGrafics. Despr�s es crida a les versions modificades de llegirEvent i tractarEvent (no cal modificar
            // aquestes crides)
           joc.ProcessEvents(); // Captura els events que s'han produit en el darrer cicle
			if (Keyboard_GetKeyTrg(KEYBOARD_LEFT))
			{
				// Si la posici� de la figura �s m�s gran que el l�mit esquerra + el despla�ament de cada moviment
				if ( posicioTetrisX >= (INICI_X + MIDA_Q))
				{
					// Movem figura a l'esquerra
					posicioTetrisX -= MIDA_Q;
				}
			} else if (Keyboard_GetKeyTrg(KEYBOARD_RIGHT))
			{
			    // Si la posici� de la figura + el tamany en horizontal de la figura �s m�s petita que el l�mit dret - el despla�ament de cada moviment
				if ( (posicioTetrisX + tetris[peca].getScaleX()) <= (FI_X - MIDA_Q) )
				{
					// Movem la figura a la dreta
					posicioTetrisX += MIDA_Q;
				}
			}
			else if (Keyboard_GetKeyTrg(KEYBOARD_DOWN))
			{
			    // Si la posici� de la figura + el tamany en vertical de la figura �s m�s petita que el l�mit inferior - el despla�ament de cada moviment
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
			    // Si la posici� de la figura no �s el final
				if (posicioTetrisY + tetris[peca].getScaleY() <= FI_Y )
				{
					// Posem la figura al fons
					posicioTetrisY = FI_Y - tetris[peca].getScaleY();
					figuraFinal = true;
				}
			}
            // ***
            // En aquest punt haureu de tornar a dibuixar el fons, les peces, el fons dels resultats, la puntuaci�
            // i el nivell actual exactament igual que heu fet m�s amunt
            // A m�s a m�s, aqu� haureu de dibuixar tamb� l'ocupaci� de l'�ltima fila cridant a la funci� pintarMeta

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
