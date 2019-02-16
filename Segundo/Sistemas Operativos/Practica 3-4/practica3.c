#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

//CONSTANTES
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
int compruebaFork(int pid){
	if(pid==ERROR){
		mensajeError();
		return 0;
	}
	return 1;
}

//Inicializa los arrays de diputados utilizados por los hijos
void inicializarArrayDiputados(int arrayDiputados[], int arrayDiputadosAux[]){
	int i;
	for(i=0;i<MAX_HIJOS;i++){
		arrayDiputados[i]=0;
		arrayDiputadosAux[i]=0;
	}
}

//Lee los elementos de la pipe de Padre a Hijo
void leerPipePaH(int pipePaH[], int *diputados){
	close (pipePaH[1]);

	char auxC[MAX_LEN_STR];
	char auxPobl[MAX_LEN_STR];

	read(pipePaH[0],&auxC,MAX_LEN_STR);
	sscanf(auxC,"%s %d", auxPobl,&(*diputados));
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

//Realiza el proceso de votacion para las 52 localidades
void circumscriciones(int pidHijos[],int pipePaH[], int pipeHaR[], int arrayDiputados[]){
        int i, diputados=0;

        for(i=0;i<MAX_HIJOS;i++){
                pidHijos[i]=fork();
                if(compruebaFork(pidHijos[i])){
                        if(pidHijos[i]==0){
                                leerPipePaH(pipePaH,&diputados);
                                asignarRandom(diputados, arrayDiputados);
                                enviarPipeHaR(pipeHaR,arrayDiputados);
                                exit(0);
                        }
                }
        }
}

//Lee la pipe de Hijo a Resultado y guarda todos los resultados en una array
void lecturaPipeHaR(int pipeHaR[], int arrayDiputados[], int arrayDiputadosAux[]){
	close(pipeHaR[1]);

	int i,j;
	for(i=0;i<MAX_HIJOS;i++){
		read(pipeHaR[0],&(*arrayDiputadosAux),(MAX_HIJOS*sizeof(int)));
        	for(j=0;j<MAX_HIJOS;j++){
        		arrayDiputados[j]+=arrayDiputadosAux[j];
                }
        }
}

//Escribe los resultados de las votaciones en el fichero
void escribeResultados(FILE *lecturaForm, FILE *escrituraResult,int arrayDiputadosAux[]){
	if(!feof(lecturaForm)&&!feof(escrituraResult)){
	        char lineaFormaciones[MAX_LEN_STR];
        	char formaciones[MAX_LEN_STR];
        	char resultado[MAX_LEN_STR];
        	int i;

   		for(i=0;i<MAX_HIJOS;i++){
      			fgets(lineaFormaciones,MAX_LEN_STR,lecturaForm);
           		sscanf(lineaFormaciones,"%s",formaciones);
           		sprintf(resultado,"%s - %d\n",formaciones,arrayDiputadosAux[i]);
           		fputs(resultado,escrituraResult);
 		}
	}
}

//Escribe en un fichero de salida, los resultados obtenidos de las votaciones
void escribeResultadosVotaciones(FILE *lecturaForm, FILE *escrituraResult, int pidResultados, int pipeHaR[], int arrayDiputados[], int arrayDiputadosAux[]){
        pidResultados=fork();

        if(compruebaFork(pidResultados)){
                if(pidResultados==0){
                        lecturaPipeHaR(pipeHaR,arrayDiputados,arrayDiputadosAux);

                        lecturaForm=fopen("formaciones.txt","r");
                        escrituraResult=fopen("resultats.txt","w");

                        escribeResultados(lecturaForm, escrituraResult,arrayDiputados);

                        fclose(lecturaForm);
                        fclose(escrituraResult);
                        exit(0);
                }
        }
}

//Lee el archivo circumscripciones para enviarselo a los hijos
void leerArchivoDiputados(FILE *lecturaCircum, int pipePaH[]){
 	lecturaCircum = fopen("circunscripciones.txt","r");

  	if(!feof(lecturaCircum)){
	        char lineaCircum[MAX_LEN_STR];
        	char localizac[MAX_LEN_STR];
        	int i;

      		close(pipePaH[0]);
     		for(i=0;i<MAX_HIJOS;i++){
       			fgets(lineaCircum,MAX_LEN_STR,lecturaCircum);
                        write(pipePaH[1],&lineaCircum,MAX_LEN_STR);
                }
      	}
 	fclose (lecturaCircum);
}

//Padre entra en bucle de MAX_HIJOS
void padreEsperaHijos(){
        int i;
        for(i=0;i<MAX_PROCESOS;i++){
                wait(NULL);
        }
}

//El proceso padre lee de un archivo y envia por una pipe las lineas a los hijos
void gestionaPadre(int pidPadre, int pipePaH[], FILE *lecturaCircum){
        if(getpid()==pidPadre){
		leerArchivoDiputados(lecturaCircum,pipePaH);
                padreEsperaHijos();
        }
}

//PRINCIPAL
int main(int argc, char** argv[]){
	//Variables
	int pipePaH[LONG_PIPE];
	int pipeHaR[LONG_PIPE];
	int pidPadre=getpid();
	int pidResultados=0;
	int pidHijos[MAX_HIJOS];
	int arrayDiputados[MAX_HIJOS];
	int arrayDiputadosAux[MAX_HIJOS];

	//Archivos de lectura/escritura
	FILE *lecturaCircum;
	FILE *lecturaForm;
	FILE *escrituraResult;

	//Creacion de pipes
	crearPipe(pipePaH);
	crearPipe(pipeHaR);

	//Inicializa los arrays de diputados
	inicializarArrayDiputados(arrayDiputados,arrayDiputadosAux);

	//Proceso de votaciones
	circumscriciones(pidHijos,pipePaH,pipeHaR,arrayDiputados);

	//Escribe los resultados en un archivo de texto
	escribeResultadosVotaciones(lecturaForm, escrituraResult, pidResultados, pipeHaR,arrayDiputados,arrayDiputadosAux);

	//Gestiona el proceso padre
	gestionaPadre(pidPadre, pipePaH, lecturaCircum);
}
