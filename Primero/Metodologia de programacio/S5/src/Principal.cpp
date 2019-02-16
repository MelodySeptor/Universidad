#include "Menu.h"
#include "Joc.h"
#include "GestioResultats.h"
#include <conio.h>      /* getch */
#include "List.h"
#include "List.cpp"
#include <iostream>
#include <string.h>

const char JUGAR = '1';
const char CONFIGURAR = '2';
const char PUNTUACIO = '3';
const char SORTIR = '4';

using namespace std;

int main()
{
	/*TipusJugador tMillorsJugadors[MAX_MILLORS_JUGADORS];

	inicialitzarTaulaMillorJugadors(tMillorsJugadors);*/

    char opcio;
    char nivell = '1';
    char nom[15] = "--------";
    List <Jugador> llista;
    Jugador ranking;

	do{
		menuPrincipal();
		opcio = _getch();

        int posicio = -1;
		int punts;

		switch(opcio)
		{
			case JUGAR:
			    punts = joc(nivell-'0');

                if(punts>0)
                {
                    system("CLS");
                    cout <<"Introdueix el teu nom:"<<endl;
                    cin >>nom;
                    strcpy(ranking.nom,nom);
                    ranking.punts = punts;
                    llista.add_end(ranking);
                    llista.sortt();
                    llista.invert();

                }
				/*posicio = esMillorPuntuacio(tMillorsJugadors, punts);

                if (posicio>=0)
				{
					system("cls");
					desplacarArray(tMillorsJugadors, posicio);
					emplenarPosicioArray(tMillorsJugadors[posicio], punts);
				}*/
				break;

			case CONFIGURAR:
				do{
                    menuNivellDificultat();
					nivell =_getch();
					if ((nivell != '1') && (nivell != '2') && (nivell != '3'))
					{
						printf("Opcio incorrecta.\n");
					}
				} while((nivell != '1') && (nivell != '2') && (nivell != '3'));
				break;
			case PUNTUACIO:
				/*escriuRanking(tMillorsJugadors);
				printf("Prem una tecla per tornar al menu principal");*/
				system("CLS");
				cout <<"=====Millors Jugadors===="<<endl<<endl;
				llista.print();
				_getch();
				break;
		}
	}while(opcio != SORTIR);

    llista.del_all();
	return 0;
}
