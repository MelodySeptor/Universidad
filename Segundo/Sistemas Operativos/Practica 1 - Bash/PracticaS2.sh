#!/bin/bash
#Mostra el menu
function mostraMenu(){
	echo "	1) Entrar el nombre del archivo con las distancias"
	echo " 	2) Mostrar las distancias entre ciudades"
	echo " 	3) Exit"
	echo "-----------------------------------------------------"
	echo "	Introduce una opcion (1/2/3):"
}

#Constants de control
declare -r ENTRAR_NOMBRE=1
declare -r MOSTRAR_DISTANCIA=2
declare -r EXIT=3

#Menu per triar opcions
function elijeOpcion(){
	clear
	if [ $1 -eq $ENTRAR_NOMBRE ]; then
		echo "Entrar el nombre del archivo con las distancias"
		echo "-----------------------------------------------"
		echo " "
		entrarNombre
	elif [ $1 -eq $MOSTRAR_DISTANCIA ]; then
		echo "Mostrar las distancias entre ciudades"
		echo "-------------------------------------"
		echo " "
		mostrarDistancia
	elif [ $1 -eq $EXIT ]; then
		echo "Presione una tecla para salir"
	else
		echo "ERROR: Introduzca una opcion valida"
	fi

	read blank
}

#Comproba si el fitxer de entrada es correcte
function comprobarFicheroEntrada(){
	if [ -f ./$1 ]; then
		linias=$(wc -l < "$1")
		echo "Leido el fichero: " $1 " con: " $linias " linias"
	else
		echo "Archivo no encontrado"
	fi
	echo " "
}

#A partir de un nom de fitxer, mira que existeixi a la mateixa carpeta
function entrarNombre(){
	echo "Introduce el nombre del archivo"
	read nombre
	if [ -f ./$nombre ]; then
		linias=$(wc -l <"$nombre")
		echo "Encontrado el fichero " $nombre " con " $linias " linias"
		fichero=$nombre
	else
		echo "ERROR: Archivo no encontrado"
	fi
	echo "Pulse una tecla para continuar"

}

#Mostra la distancia de un Origen a un Desti
function mostrarDistancia(){
	if [ -f ./$fichero ]; then
		echo "Introduce la ciudad origen"
		read ciuOrig
		echo "Introduce la ciudad destino"
		read ciuDest
		leerFichero $ciuOrig $ciuDest
	else
		echo "ERROR: Archivo no encontrado"
	fi
		echo "Pulsa una tecla para salir"
}

#Llegir del fitxer  les dades que es pasen i imprimeix la distancia que hi ha entre elles
function leerFichero(){
	aux="$1:$2"
	buscarPatron=$( grep -c -i "$1:$2" ./$fichero)

	if [ $buscarPatron -ne 0 ]; then
		LINEA=$( grep -i "$1:$2" ./$fichero )
		IFS=':'
		arrayAux=( $LINEA )
		LINEA="${arrayAux[2]}"
		echo " "
		echo "De $1 hasta $2 hay $LINEA Km"
	else
		echo "ERROR: La pareja de ciudades solicitada no existe"
	fi
}

#Llegir del fitxer quina dada es la mes gran
function vwMxDs(){
	echo "No implementada"
}

opcion=0
fichero=""

clear

fichero=$1
while [ $opcion -ne $EXIT ]; do
	comprobarFicheroEntrada $fichero
	mostraMenu
	read opcion
	elijeOpcion $opcion
	clear
done
