#include "Joc.h"

//////////////CONTROL/////////////////////////////////////////
//Posa el text a color LIGHTGREY abans de sortir del joc
void reiniciaText(HANDLE hScreen) {
	TextColor(LIGHTGREY, BLACK, hScreen);
}

//Retorna un numero aleatori entre els que s'introdueixen
int aleatori(int numInici, int numMax) {
	srand(time(NULL));
	int aux = rand() % (numMax - numInici + 1) + numInici;
	return (aux);
}
//////////////FI CONTROL//////////////////////////////////////////

/////////////////PINTA///////////////////
//Pinta un objecte a una posició determinada
void pintarObjecte(int posX, int posY, int colorObj, int colorFons, char obj, HANDLE hScreen) {
	TextColor(colorObj, colorFons, hScreen);
	GotoXY(posX, posY, hScreen);
	printf("%c", obj);
}

//Pinta uns punts que li pasem
void pintarPunts(int punts, HANDLE hScreen) {
	TextColor(LIGHTGREY, BLACK, hScreen);
	GotoXY(POS_PUNTS_X, POS_PUNTS_Y, hScreen);
	printf("PUNTS: %d", punts);
}

//Pinta les vides que li pasem
void pintarVides(int vides, HANDLE hScreen) {
	TextColor(LIGHTGREY, BLACK, hScreen);
	GotoXY(POS_VIDES_X, POS_VIDES_Y, hScreen);
	printf("VIDES: %d", vides);
}

//Pinta el nivell que es pasa desde el main
void pintarNivell(int nivell, HANDLE hScreen) {
	TextColor(LIGHTGREY, BLACK, hScreen);
	GotoXY(POS_NIVELL_X, POS_NIVELL_Y, hScreen);
	printf("NIVELL: %d",nivell);
}

//Pinta de color negre tot el fons (per eliminar qualsevol
//resta de brosa que hi hagi)
void pintarFons(HANDLE hScreen) {
	for (int i = INICI_X;i < FI_X;i++) {
		for (int j = INICI_Y;j < FI_Y;j++) {
			pintarObjecte(i, j, BLACK, BLACK, FONS, hScreen);
		}
	}
}

//Comproba si es pot pintar el MUR
int comprobaPintaMur(int x, int y) {
	if (((y >= INICI_Y_MUR) && (y <= FI_Y_MUR) && ((x == INICI_X_MUR) || (x == FI_X_MUR))) || (y == INICI_Y_MUR)) 
		return 1;
	
	else
		return 0;
}

//Pinta el mur unicament per els extrems
void pintarMur(HANDLE hScreen) {
	for (int x = INICI_X_MUR;x <= FI_X_MUR;x++) {
		for (int y = INICI_Y_MUR;y <= FI_Y_MUR;y++) {
			if (comprobaPintaMur(x,y)) 
				pintarObjecte(x, y, LIGHTGREY, BLACK, MUR, hScreen);
		}
	}
}

//Pinta tot el que va al taulell: fons, nivell, punts, vides i mur
void pintaTaulell(HANDLE hScreen, control varControl, int nivell) {
	pintarNivell(nivell,hScreen);
	pintarPunts(varControl.punts,hScreen);
	pintarVides(varControl.vides,hScreen);
	pintarMur(hScreen);
}

//Pinta una linea adalt de tot
void pintaLineaJoc(HANDLE hScreen, lineaJoc &varLineaJoc) {
	for (int x = INICI_X_MUR + 1;x < FI_X_MUR;x++) {
		if (varLineaJoc.arrayMur[x] == PINTAT)
			pintarObjecte(x, POS_LINEA_JOC, varLineaJoc.color, BLACK, MUR, hScreen);
		else
			pintarObjecte(x, POS_LINEA_JOC, BLACK, BLACK, MUR, hScreen);
	}
}

//Pinta la pilota a partir de una posicio que es pasa
void pintaPilota(HANDLE hScreen, pilota varPilota) {
	pintarObjecte(varPilota.posX, varPilota.posY, LIGHTGREEN, BLACK, PILOTA, hScreen);
}

//Esborra la pilota en la posicio que estigui
void esborrarPilota(HANDLE hScreen, pilota varPilota) {
	pintarObjecte(varPilota.posX, varPilota.posY, BLACK, BLACK, PILOTA, hScreen);
}

//Pinta la pala a partir de una posicio que es pasa
void pintaPala(HANDLE hScreen, int posX) {
	for (int i = posX - PALA_AMPLADA_DIBUIXA; i <= posX + PALA_AMPLADA_DIBUIXA;i++) {
		pintarObjecte(i, FI_Y_MUR, RED, BLACK, OFFSET, hScreen);
	}
}

//Esborra la pala
void esborrarPala(HANDLE hScreen, int posX) {
	for (int i = posX - OFFSET;i <= posX + OFFSET;i++) {
		pintarObjecte(i, FI_Y_MUR, BLACK, BLACK, OFFSET, hScreen);
	}
}

//Pinta GAMEOVER
void pintarGameOver(HANDLE hScreen) {
	TextColor(LIGHTRED, BLACK, hScreen);
	//-1 perque quedi alineat (pasa segons el text que es pinti
	GotoXY(PINTA_ESTAT_X,PINTA_ESTAT_Y, hScreen);
	printf("GAME OVER!");
}

//Pinta Guanyat
void pintarGuanyar(HANDLE hScreen) {
	TextColor(LIGHTGREEN, BLACK, hScreen);
	//-1 perque quedi alineat (pasa segons el text que es pinti
	GotoXY(PINTA_ESTAT_X,PINTA_ESTAT_Y, hScreen);
	printf("HAS GUANYAT!");
}
/////////////FI PINTA////////////////////

/////////////INICIALITZACIONS///////////////
//Inicialitza el array de control:
// 0-No esta pintat
// 1-Esta pintat
void inicialitzaLineaJoc(lineaJoc &varLineaJoc) {
	for (int i = 0;i < MAX_LLARG_LINEA;i++) {
		if ((i <= INICI_X_MUR) || (i >= FI_X_MUR))
			varLineaJoc.arrayMur[i] = NO_PINTAT;
		else
			varLineaJoc.arrayMur[i] = PINTAT;
	}
}

//Inicialitza dades de pilota
void inicialitzaPilota(pilota &varPilota, int posPalaX) {
	varPilota.posX = posPalaX;
	varPilota.posY = POS_INIC_PILOTA_Y;
	varPilota.dirX = MOURE_ADALT;
	varPilota.dirY = MOURE_DRETA;
}

//Inicialitza la pala
void inicialitzaPala(pala &varPala) {
	varPala.posX = aleatori(PALA_MIN_X_ALEATORI, PALA_MAX_X_ALEATORI);
}

//Inicia les posicions
void inicialitzaPosicions(pilota &varPilota, pala &varPala) {
	inicialitzaPala(varPala);
	inicialitzaPilota(varPilota, varPala.posX);
}

//Inicialitza les variables de control
void inicialitzaControl(control &varControl, int nivell) {
	varControl.perdut = PERDUT;
	varControl.contador = VELOCITAT_PILOTA / nivell;
}

//Inicia la primera pintada per pantalla
void pintaPantallaNova(HANDLE hScreen, int &posPalaX, pilota &varPilota, lineaJoc &varLineaJoc) {
	pintarFons(hScreen);
	pintaLineaJoc(hScreen, varLineaJoc);
	pintaPala(hScreen, posPalaX);
	pintaPilota(hScreen, varPilota);
}

//Pinta per primer cop el joc
void inicialitzaPantalla(HANDLE hScreen, pilota &varPilota, pala &varPala, lineaJoc &varLineaJoc, control &varControl, int nivell) {
	inicialitzaControl(varControl, nivell);
	inicialitzaPosicions(varPilota, varPala);
	pintaPantallaNova(hScreen, varPala.posX, varPilota, varLineaJoc);
}
/////////////FI INICALITZACIONS////////////////////

////////////CONTROL DE LA PALA/////////////////////
//Mira si la pala es pot mure
int palaLimits(int posX,int dirX, HANDLE hScreen) {
	if (((posX - OFFSET) + dirX<=INICI_X_MUR) || ((posX + OFFSET) + dirX>=FI_X_MUR)) {
		return  0;
	}
	else
		return 1;
}

//A traves de la direccio que es pasa es mou la pala
void mourePala(int &posX, int dirX, HANDLE hScreen) {
	if (palaLimits(posX, dirX, hScreen)) {
		esborrarPala(hScreen, posX);
		posX += dirX;
		pintaPala(hScreen, posX);
	}
}
////////////FI CONTROL PALA/////////////////////////

////////////CONTROL PILOTA//////////////////////////
//Asigna una direcció
void asignaDireccioPilota(pilota &varPilota, int x, int y) {
	varPilota.dirX = x;
	varPilota.dirY = y;
}

//Mira si la pilota xoca amb la pala
int pilotaXocaPala(int posPalaX, pilota varPilota) {
	int control = 0;
	for (int i = posPalaX - OFFSET-1;i <= posPalaX + OFFSET+1;i++) {
		if ((varPilota.posY >= POS_INIC_PILOTA_Y) && ((varPilota.posX==i)))
			control = 1;
	}
	return control;
}

//Eliminar on colisioni la pilota de la linea de joc
void eliminaLineaJoc(int posX,lineaJoc &varLineaJoc,control &varControl, int nivell) {
	for (int i = posX - 1;i <= posX + 1;i++) {
		if (varLineaJoc.arrayMur[i] == PINTAT)
			varControl.punts = varControl.punts + (nivell*100);
		varLineaJoc.arrayMur[i] = NO_PINTAT;
	}	
}

//Comproba si on xoca la pilota esta pintat
int comprobaPilotaLineaEsPintada(pilota varPilota, lineaJoc &varLineaJoc) {
	if ((varPilota.posY + varPilota.dirY <= INICI_Y_MUR) || ((varPilota.posY + varPilota.dirY < INICI_Y_MUR + OFFSET)&&(varLineaJoc.arrayMur[varPilota.posX+varPilota.dirX] == PINTAT)))
		return 1;
	else
		return 0;
}

//Comproba cap on ha de moure's la pilota
void comprobarDireccioPilotaEsquerra(pilota &varPilota) {
	if (varPilota.posX + varPilota.dirX <= INICI_X_MUR) {
		asignaDireccioPilota(varPilota, MOURE_ADALT, MOURE_ESQUERRA);
	}
}
void comprobarDireccioPilotaDreta(pilota &varPilota) {
	if (varPilota.posX + varPilota.dirX >= FI_X_MUR) {
		asignaDireccioPilota(varPilota, MOURE_ABAIX, MOURE_DRETA);
	}
}
void comprobarDireccioPilotaAdalt(pilota &varPilota, lineaJoc &varLineaJoc, control &varControl,int nivell) {
	if (comprobaPilotaLineaEsPintada(varPilota,varLineaJoc)) {
		eliminaLineaJoc(varPilota.posX, varLineaJoc,varControl, nivell);
		asignaDireccioPilota(varPilota, MOURE_ABAIX, MOURE_ESQUERRA);
	}
}
void comprobarDireccioPilotaAvall(pala varPala, pilota &varPilota) {
	if (pilotaXocaPala(varPala.posX, varPilota)) {
		asignaDireccioPilota(varPilota, aleatori(MOURE_ABAIX,OFFSET), MOURE_DRETA);
	}
}

//Mira si la pilota es fora dels limits, si es aixi
//has perdut
int pilotaAbaixPala(int posY, int &perdut) {
	if (posY >= FI_Y_MUR) {
		perdut = 1;
	}
	return perdut;
}

//Comproba si la pilota es troba dins del taulell
void triaDireccio(pala varPala, pilota &varPilota, control &varControl, lineaJoc &varLineaJoc,int nivell) {
	if(!pilotaAbaixPala(varPilota.posY,varControl.perdut)) {
		comprobarDireccioPilotaEsquerra(varPilota);
		comprobarDireccioPilotaDreta(varPilota);
		comprobarDireccioPilotaAdalt(varPilota, varLineaJoc,varControl,nivell);
		comprobarDireccioPilotaAvall(varPala, varPilota);
	}
}

//Mou la pilota
void mourePilota(pala varPala, pilota &varPilota, control &varControl , lineaJoc &varLineaJoc, HANDLE hScreen, int nivell) {
	triaDireccio(varPala, varPilota, varControl, varLineaJoc, nivell);
	esborrarPilota(hScreen, varPilota);
	varPilota.posX += varPilota.dirX;
	varPilota.posY += varPilota.dirY;
	pintaPilota(hScreen, varPilota);
}
//////////////FI CONTROL PILOTA/////////////////////////////////

////////////////CONTROL DEL JOC/////////////////////////////////
//Mode test amb la t, per pasar de nivell directament
void test(lineaJoc &varLineaJoc) {
	for (int i = 0;i < MAX_LLARG_LINEA;i++) {
		varLineaJoc.arrayMur[i] = NO_PINTAT;
	}
}

//A partir de la tecla que es pica es fan accions
void premTecla(control varControl, int &posX,lineaJoc &varLineaJoc, HANDLE hScreen) {
	switch (varControl.tecla) {
	case DRETA: mourePala(posX, MOURE_DRETA, hScreen);break;
	case ESQUERRA: mourePala(posX, MOURE_ESQUERRA, hScreen);break;
	case ESCAPE: pintarGameOver(hScreen);break;
	case TEST:test(varLineaJoc); break;
	default:
		break;
	}
}

//Llegeix la tecla que s'ha apretat
void llegirTecla(control &varControl, pala &varPala, lineaJoc &varLineaJoc, HANDLE hScreen) {
	if (_kbhit()) {
		varControl.tecla = _getch();
		premTecla(varControl, varPala.posX,varLineaJoc, hScreen);
	}
}

//Mostra GameOver/Has guanyat
void modeJocFinal(HANDLE hScreen, int mode) {
	if ((mode == PERDUT)||(mode==ESCAPE)) {
		pintarGameOver(hScreen);
	}
	if (mode == GUANYAT) {
		pintarGuanyar(hScreen);
	}
	char pauseTecla = _getch();
}

//Mira si has perdut el joc
void jocPerdut(control &varControl,HANDLE hScreen) {
	if (varControl.perdut) {
		varControl.vides--;
		pintarVides(varControl.vides,hScreen);
		modeJocFinal(hScreen, PERDUT);
	}
}

//Comproba cuantes posicions de la linea de joc estan pintades
void comprobaLineaJocPintada(lineaJoc &varLineaJoc,int &comprobador) {
	for (int i = 0;i < MAX_LLARG_LINEA;i++) {
		if (varLineaJoc.arrayMur[i] == NO_PINTAT) {
			comprobador++;
		}
	}
}

//Comproba que la linea del joc estigui esborrada
int lineaJocNoPintada(lineaJoc &varLineaJoc) {
	int comprobador = 0;
	comprobaLineaJocPintada(varLineaJoc, comprobador);
	if (comprobador >= MAX_LLARG_LINEA) {
		return 1;
	}
	return 0;
}

//Mira si hem guanyat el joc
//retorna 1 si se ha guanyat
//retorna 0 si no se ha guanyat
int jocGuanyat(lineaJoc &varLineaJoc, int &nivell, HANDLE hScreen) {
	if (lineaJocNoPintada(varLineaJoc)) {
		nivell++;
		inicialitzaLineaJoc(varLineaJoc);
		modeJocFinal(hScreen, GUANYAT);
		return 1;
	}
	return 0;
}

//Fa que la pilota es pugi moure, comprobant on xoca en tot moment i quines repercusions tindrà
void movimentJoc(pala varPala, pilota &varPilota,lineaJoc &varLineaJoc,control &varControl, int nivell, HANDLE hScreen) {
	varControl.contador--;
	if (varControl.contador == 0) {
		varControl.contador = VELOCITAT_PILOTA / nivell;
		pintaLineaJoc(hScreen, varLineaJoc);
		mourePilota(varPala, varPilota, varControl, varLineaJoc, hScreen,nivell);
	}
}

//Mira si s'ha completat una partida
int partidaCompletada(control &varControl, lineaJoc &varLineaJoc, int &nivell, HANDLE hScreen) {
	if ((varControl.perdut == 1) || (varControl.tecla == ESCAPE) || (jocGuanyat(varLineaJoc, nivell, hScreen))) {
		return 1;
	}
	return 0;
}

//Mira si el joc s'ha completat
int jocCompletat(control &varControl, int nivell) {
	if ((varControl.tecla == ESCAPE) || (varControl.vides == 0) || (nivell == MAX_NIVELL)) {
		return 1;
	}
	return 0;
}
//////////////FI CONTROL DEL JOC///////////////////////////////

//FUNCIO JOC
int joc(int nivell) {
	//Crea objecte de HANDLE i fa les inicialitzacions
	HANDLE hScreen;
	hScreen = GetStdHandle(STD_OUTPUT_HANDLE);
	InitScreen(hScreen);
	musicaJocON();

	//Variable de control
	control varControl;

	//Variables de Joc
	pilota varPilota;
	pala varPala;
	lineaJoc varLineaJoc;

	//Netejem pantalla
	system("cls");

	//Inicia les posicions
	inicialitzaLineaJoc(varLineaJoc);

	//Bucle pricipal que va pintant el taulell i els objectes pilota i pala
	//Acaba quant es prem ESC, perdem partida o be guanyem MAX nivell
	do{
		inicialitzaPantalla(hScreen, varPilota, varPala, varLineaJoc,varControl,nivell);
		do {
			//Pinta
			pintaTaulell(hScreen, varControl, nivell);
			pintaPala(hScreen, varPala.posX);

			//Mou tot el joc
			movimentJoc(varPala, varPilota, varLineaJoc, varControl, nivell, hScreen);

			//Llegeix la tecla
			llegirTecla(varControl, varPala,varLineaJoc, hScreen);

			//Comproba si s'ha perdut en el joc
			jocPerdut(varControl, hScreen);

		} while (!partidaCompletada(varControl,varLineaJoc,nivell,hScreen));
	} while(!jocCompletat(varControl,nivell));

	//Si sortim amb ESCAPE ho controla
	modeJocFinal(hScreen, varControl.tecla);

	//Posa el text a color altre cop
	reiniciaText(hScreen);
	pararMusica();

	//Retorna punts
	return varControl.punts;
}
