#include "Configurar.h"

//Menu de configuracio
void menuConfig() {
	system("cls");
	printf("---------CONFIGURACIO----------\n\n");
	printf("1- Facil\n");
	printf("2- Normal\n");
	printf("3- Dificil\n");
}

//Asigna un nivell a partir de un char
int asignaNivel(char &tecla) {
	tecla = _getch();
	return(tecla - CONVERSION_CHAR_INT);
}

//Funcio per triar el nivell
int configurar() {
	char tecla;
	int nivell;
	
	do
	{
		menuConfig();
		nivell = asignaNivel(tecla);
	} while ((tecla!=LV1)&&(tecla!=LV2)&&(tecla!=LV3));
	return nivell;
}