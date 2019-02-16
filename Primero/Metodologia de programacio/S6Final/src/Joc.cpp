
#include "Joc.h"
#include "../lib/libreria.h"
#include <cstdlib>

#include "Resultats.h"

using namespace std;

//Mira la tecla que s'ha apretar
int llegirEvent()
{
    int tecla;

    if (Keyboard_GetKeyTrg(KEYBOARD_LEFT))
        tecla = TECLA_ESQUERRA;
    else
        if (Keyboard_GetKeyTrg(KEYBOARD_RIGHT))
            tecla = TECLA_DRETA;
        else
            if (Keyboard_GetKeyTrg(KEYBOARD_DOWN))
                tecla = TECLA_ABAIX;
            else
                if (Keyboard_GetKeyTrg(KEYBOARD_ESCAPE))
                    tecla = TECLA_ESC;
                    else
                        if(Keyboard_GetKeyTrg(KEYBOARD_UP))
                        tecla = TECLA_ADALT;
                        else
                            if(Keyboard_GetKeyTrg(KEYBOARD_SPACE))
                            tecla = TECLA_ESPAI;
    return tecla;
}

//Aleatori per iniciX
int aleatori(int min, int max)
{
	int aleatori = rand() % (max - min + 1) + min;
	return aleatori;
}

//Fa una accio o altre segons una tecla
void tractarEvent(int tecla, FigTetris& fig, Fons& fons)
{
	// TODO
	// Adaptar el mateix tractament de cada possible event (tecla) que vau fer a la sessió 1, modificant el codi per
	// utilitzar els mètodes de les classes FigTetris i Fons
    switch (tecla)
	{
	    case TECLA_ESQUERRA:
	        fig.moureFig(-1,0,fons);
	        break;
	    case TECLA_DRETA:
	        fig.moureFig(1,0,fons);
	        break;
	    case TECLA_ABAIX:
	        fig.moureFig(0,1,fons);
	        break;
        case TECLA_ADALT:
        case TECLA_ESPAI:
            fig.girarFig(fons);
            break;
                }
}

//Crea les diferents figures en un array
void crearFigTetris(FigTetris* figTetrisActual)
{
    for(int i=0;i<MAX_FIG;i++)
    {
        figTetrisActual[i].create(i);
    }
}

//Comença la gresca
int joc(int nivell)
{
    //INICIALITZACIONS!
    Game joc;
	joc.Init();
    Fons fons;
    Resultats resultat;

    int tecla = 0; // Valor de la tecla pressionada en cada iteració del joc
    bool metaAconseguida; // Indica si la figura ha arribat a la última línia del taules
    bool finalTemps; // Indica si se'ns ha acabat el temps per completar la última línia del tauler
	int velocitatJoc = 500; // Indica velocitat del joc, quantes més linies es fan més ràpida és
	int contVPeca; // Comptador per controlar la velocitat
	int vides = 3; // Nº de vides
	int punts = 0; // Punts
	int diffT = 0; // Control del temps del joc

	srand((unsigned)time(NULL));

    fons.inicialitzar("data/GraficsTetris/fons.png");
    resultat.inicialitzar("data/GraficsTetris/Resultats.png");

    joc.Video_ShowWindow();

    FigTetris figura[MAX_FIG];
    crearFigTetris(figura);

	do
    {
        //MÉS INICIALITZACIONS
        int indexFig =aleatori(INI_FIG, FI_FIG);
        int posX = ( (INICI_X) + ( ( rand() % ( ( (FI_X - INICI_X - (figura[indexFig].amplada())) / MIDA_Q ) + 1 ) ) * MIDA_Q ));
        int posY = INICI_Y;
        figura[indexFig].reiniciarGir();
        figura[indexFig].setPosX(posX);
        figura[indexFig].setPosY(posY);

        metaAconseguida = false;
        contVPeca = velocitatJoc / nivell;

        //PINTEM
        fons.pintaFons();
        resultat.pintaResultats(nivell, punts,vides);
        figura[indexFig].draw();

        //REFRESQUEM
        joc.VideoUpdate();

        do
        {
            //MIREM LA TECLA PREMUDA
           joc.ProcessEvents();
            tecla = llegirEvent();
            tractarEvent(tecla, figura[indexFig], fons);

            contVPeca--;

            //CONTADOOR PER SABER SI ARRIBA ABAIX
            if(contVPeca == 0)
            {

                bool encaixada = figura[indexFig].moureFig(0, 1, fons);
                if (encaixada)
                    {
                        metaAconseguida = true;
                    }
                contVPeca = velocitatJoc / nivell;
            }

            //PINTEM ALTRE COP
            fons.pintaFons();
            resultat.pintaResultats(nivell,punts,vides);
            figura[indexFig].draw();

            //REFRESQUEM
            joc.VideoUpdate();

            //MIRA SI SOM DE MAGISTERI Y HEM PERDUT
            if ((fons.perdre()))
            {
                fons.posarNegre();
                vides--;
                fons.saberiPerd(false);
            }

            //MIRA SI HEM GUANYAT
            if(fons.guanyar())
            {
                metaAconseguida = true;
                punts += nivell;
                nivell++;
            }

        }while((tecla != TECLA_ESC) && (!metaAconseguida) && (!finalTemps) && (vides>0));

	}while((nivell<MAX_NIVELL) && (vides>0) && (tecla != TECLA_ESC));

    //RETORNA LA TEVA SKILL
	return punts;
}
