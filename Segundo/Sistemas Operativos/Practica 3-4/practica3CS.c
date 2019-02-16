#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>
#include <fcntl.h>

#define LONG_PIPE 2
#define MAX_HIJOS 51
#define MAX_PROCESOS 52
#define ERROR -1
#define MSG_ERROR "Error de creacion"
#define MAX_LEN_STR 64

//Muestra un mensaje de error
void mensajeError(){
	write(1,MSG_ERROR,strlen(MSG_ERROR));
}

//Crea una pipe comprobando si se hace bien
void crearPipe(int pipeN[]){
	if(pipe(pipeN)==ERROR)
		mensajeError();
}

//Mira si se ha creado bien el hijo
int comprobaFork(int pid){
	if(pid==ERROR){
		mensajeError();
		return 0;
	}
	return 1;
}

//Inicializa los arrays de diputados utilizados por los hijos
void inicializarDiputados(int arrayDiputados[], int arrayDiputadosAux[]){
	int i=0;
	for(i=0;i<MAX_HIJOS;i++){
		arrayDiputados[i]=0;
		arrayDiputadosAux[i]=0;
	}
}

//Lee los elementos de la pipe de Padre a Hijo
void leerPipePaH(int pipePaH[], int *diputados){
	close (pipePaH[1]);
	read(pipePaH[0],&(*diputados),sizeof(int));
}

//Asigna un random para la circumscripcion
void asignarRandom(int diputados, int arrayDiputados[]){
	int posRand=0;
	int diputadosRand=0;
	srand(getpid());

	while((diputados>0)||(diputados!=0)){
        	posRand=rand()%(MAX_HIJOS);
                diputadosRand=rand()%(diputados+1);
                arrayDiputados[posRand]=diputadosRand;
                diputados=diputados - diputadosRand;
        }

}

//Pasa de lo pipe de Hijos a resultados
void enviarPipeHaR(int pipeHaR[], int arrayDiputados[]){
	close(pipeHaR[0]);
        write(pipeHaR[1],&(*arrayDiputados),(MAX_HIJOS*sizeof(int)));
}

//Padre entra en bucle de MAX_HIJOS
void padreEsperaHijos(){
	int j;
	for(j=0;j<MAX_PROCESOS;j++){
        	wait(NULL);
        }
}

//PRINCIPAL
int main(int argc, char** argv[]){
	int pipePaH[LONG_PIPE];
	int pipeHaR[LONG_PIPE];
	int pidPadre=getpid();
	int pidResultados=0;
	int pidHijos[MAX_HIJOS];
	int diputados=0;
	int arrayDiputados[MAX_HIJOS];
	int arrayDiputadosAux[MAX_HIJOS];
	int i=0;
	int j=0;

	FILE *lecturaCircum;
	FILE *lecturaForm;
	FILE *escrituraResult;

	//CREAR PIPE
	crearPipe(pipePaH);
	crearPipe(pipeHaR);

	//Inicializa los diputados
	inicializarDiputados(arrayDiputados,arrayDiputadosAux);

	//CREA FILLS
	for(i=0;i<MAX_HIJOS;i++){
		pidHijos[i]=fork();
		if(comprobaFork(pidHijos[i])){
			if(pidHijos[i]==0){
				leerPipePaH(pipePaH,&diputados);
				asignarRandom(diputados, arrayDiputados);
				enviarPipeHaR(pipeHaR,arrayDiputados);
				exit(0);
			}
		}
	}

	//RESULTADOS
	pidResultados=fork();
	if(!comprobaFork(pidResultados)){
		mensajeError();
	}
	else if(pidResultados==0){
		close(pipeHaR[1]);
		for(i=0;i<MAX_HIJOS;i++){
			read(pipeHaR[0],&arrayDiputados,sizeof(arrayDiputados));
			for(j=0;j<MAX_HIJOS;j++){
				arrayDiputadosAux[j]+=arrayDiputados[j];
			}
		}
		lecturaForm=fopen("formaciones.txt","r");
		escrituraResult=fopen("resultats.txt","w");

		char lineaFormaciones[MAX_LEN_STR];
		int z=0;
		char formaciones[MAX_LEN_STR];
		char resultado[MAX_LEN_STR];
		for(z=0;z<MAX_HIJOS;z++){
			fgets(lineaFormaciones,MAX_LEN_STR,lecturaForm);
			sscanf(lineaFormaciones,"%s",formaciones);
			sprintf(resultado,"%s - %d\n",formaciones,arrayDiputadosAux[z]);
			fputs(resultado,escrituraResult);
		}
		fclose(lecturaForm);
		fclose(escrituraResult);
		exit(0);
	}

	//PARE ESPERA FILLS
	if(getpid()==pidPadre){
		char lineaCircum[MAX_LEN_STR];
		char localizac[MAX_LEN_STR];

		//Leer de txt
		//FALTA PASAR NOMBRE TAMBIEN ES INUTIL PERO BUENO EL PDF MANDA!
		lecturaCircum = fopen("circunscripciones.txt","r");
		if(!feof(lecturaCircum)){
			close(pipePaH[0]);
			for(j=0;j<MAX_HIJOS;j++){
				fgets(lineaCircum,MAX_LEN_STR,lecturaCircum);
				sscanf(lineaCircum,"%s %d", localizac,&diputados);
				write(pipePaH[1],&diputados,sizeof(int));
			}
		}
		fclose (lecturaCircum);

		//Padre espera a que hijos terminen
		padreEsperaHijos();
	}
}

