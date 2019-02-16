#include "Menu.h"
#include "Joc.h"
#include <conio.h>      /* getch */
#include "List.h"
#include "List.cpp"
#include <iostream>
#include <string.h>

//Constants
const char JUGAR = '1';
const char CONFIGURAR = '2';
const char PUNTUACIO = '3';
const char SORTIR = '4';
const string rutaArxiu = "data/arxius/LlistaJugadors.txt";

using namespace std;

//Aqui comença tot :o
int main()
{
    //Inicialitzacions
    char opcio;
    char nivell = '1';
    char nom[15] = "--------";
    char opcion = '0';

    List <Jugador> llista;
    Jugador ranking;

    //carga el arxiu y posa que tingi color blanc la consola, aixi queda millor
    llista.cargarArxiu(rutaArxiu);
    system("color 0F");

	do{
        //Mostrem el menu y triem la opcio
		menuPrincipal();
		opcio = _getch();

        int posicio = -1;
		int punts;

		switch(opcio)
		{
			case JUGAR:
			    //Jugem
			    punts = joc(nivell-'0');

                if(punts>0)
                {
                    system("CLS");
                    cout <<"Introdueix el teu nom:"<<endl;
                    cin >>nom;

                    //Fem coses varies per posar la llista ven ordenadeta y correcte
                    strcpy(ranking.nom,nom);
                    ranking.punts = punts;
                    llista.afageixNode(ranking);
                    llista.ordenaLlista();
                    llista.invertirLlista();

                }
				break;

			case CONFIGURAR:

			    do{
			    menuOpcions();
			    opcion = getch();

			    //Nova opcio per borrar la llista, made myself
			    if(opcion =='1')
                {
                    if(!llista.esBuida())
                    {
                    llista.esborraLlista();
                    llista.guardarArxiu(rutaArxiu);
                    }
                }

                //La que hi habia abans de la dificultad
			    if(opcion=='2')
                {

				do{
                    menuNivellDificultat();
					nivell =_getch();
					if ((nivell != '1') && (nivell != '2') && (nivell != '3'))
					{
						printf("Opcio incorrecta.\n");
					}
				} while((nivell != '1') && (nivell != '2') && (nivell != '3'));
                }
			    }while((opcion!='1')&&(opcion!='2')&&(opcion!='3'));
				break;
			case PUNTUACIO:
			    //Mostra per pantalla
				system("CLS");
				cout <<"===== Millors Jugadors ====="<<endl<<endl;
				llista.mostraLlista();
				cout <<"============================"<<endl<<endl;
				cout <<"Prem una tecla per continuar"<<endl;
				_getch();
				break;
		}
	}while(opcio != SORTIR);

	if(!llista.esBuida())
    {
    //Guardem a arxiu y borrem la llista per acabar
    llista.guardarArxiu(rutaArxiu);
    llista.esborraLlista();
    }

	return 0;
}
