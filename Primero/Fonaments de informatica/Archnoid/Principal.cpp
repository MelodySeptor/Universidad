#include "Principal.h"

//Mostra menu
void menuPrincipal() {
	system("cls");
	printf("---------MENU PRINCIPAL----------");
	printf("\n1) Jugar\n2) Configurar\n3) Millors Puntuacions\n4) Sortir\n");
}

//Llegeix el nom de la persona despres de jugar
void llegeixNom(controlPrincipal &varControlPrincipal) {
	system("cls");
	printf("Introdueix el teu nom:\n");
	gets_s(varControlPrincipal.nom);
}
//Gestiona la entrada i sortida del joc
void gestionaJoc(Jugador llistaJugadors[], controlPrincipal &varControlPrincipal) {
	pararMusica();
	varControlPrincipal.punts = joc(varControlPrincipal.nivell);
	llegeixNom(varControlPrincipal);
	insertaNouOrdenat(llistaJugadors, varControlPrincipal.punts, varControlPrincipal.nom);
	musicaMenuON();
}

//Triar una opcio del menu
void triarOpcio(controlPrincipal &varControlPrincipal, Jugador llistaJugadors[]) {
	switch (varControlPrincipal.opcio)
	{
	case JUGAR:gestionaJoc(llistaJugadors, varControlPrincipal);break;
	case CONFIGURAR:varControlPrincipal.nivell = configurar();break;
	case PUNTUACIO:resultats(llistaJugadors); break;
	default:
		break;
	}
}

//MAIN
int main() {
	//Variables de control
	Jugador llistaJugadors[MAX_JUGADORS];
	controlPrincipal varControlPrincipal;

	do {
		musicaMenuON();

		//Mostra menu i rep opcio
		menuPrincipal();
		varControlPrincipal.opcio = _getch();

		//Evalua la opcio i actua
		triarOpcio(varControlPrincipal, llistaJugadors);
	} while (varControlPrincipal.opcio!=SORTIR);
	return 0;
}