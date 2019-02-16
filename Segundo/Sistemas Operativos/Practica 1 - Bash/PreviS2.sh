#!/bin/bash

function mostraMenu(){
	echo "	1) Entrar el nombre del archivo con las distancias"
	echo " 	2) Mostrar las distancias entre ciudades"
	echo " 	3) Exit"
	echo "-----------------------------------------------------"
	echo "	Introduce una opcion (1/2/3):"
}

declare -r ENTRAR_NOMBRE=1
declare -r MOSTRAR_DISTANCIA=2
declare -r EXIT=3

function elijeOpcion(){
	clear
	if [ $1 -eq $ENTRAR_NOMBRE ]; then
		echo "Entrar el nombre del archivo con las distancias"
	elif [ $1 -eq $MOSTRAR_DISTANCIA ]; then
		echo "Mostrar las distancias entre ciudades"
	elif [ $1 -eq $EXIT ]; then
		echo "Presione una tecla para salir"
	else
		echo "ERROR: Introduzca una opcion valida"
	fi

	read blank
}

opcion=0
condicion=3

CONTADOR=0
clear

while [ $opcion -ne $condicion ]; do
	mostraMenu
	read opcion
	elijeOpcion $opcion
	clear
done
