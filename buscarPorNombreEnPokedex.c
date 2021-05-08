#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Map.h"

typedef struct{
	int id;
	char* nombre;
	int PC;
	int PS;
	char* sexo;
}Pokemon_usuario;

typedef struct{
	char* nombre;
	int existencia;
	char* tipo;
	char* evolucionPrevia;
	char* evolucionPosterior;
	int numeroPokedex;
	char* region;
}Pokedex;

void buscarPorNombreEnPokedex(Map *Pokedex_nombre){
	// Si el mapa no se encuentra inicializado, se imprime un mensaje y se vuelve al menu de opciones. //
	if(Pokedex_nombre == NULL){
		printf("No se tiene registro previo para realizar esta funcion\n\n");
		return;
	}

	// Declaración de variables. //
	bool existeRegistroPokemon = false;
	char nombre[50], num[10];
	int k, espacios;
	printf("Ingrese nombre de Pokemon: ");
	scanf("%[^\n]s", nombre);
	getchar();

	// Se busca en la Pokedex y se imprime la información del Pokemon con el nombre ingresado. //
	Pokedex *aux = (Pokedex*) searchMap(Pokedex_nombre, nombre);

	// Si se encuentra el pokemon, se muestra la informacion de la Pokedex
	if(aux){
		printf("Pokemon %s:\n", nombre);
		printf(" ---------------------------------------------------------------------------------------------------------------------------------------------------------------- \n");
		printf("| NOMBRE               | TIPO(S)                        | EVOLUCION PREVIA     | EVOLUCION POSTERIOR  | NUMERO POKEDEX       | REGION               | EXISTENCIA |\n");
		printf(" ---------------------------------------------------------------------------------------------------------------------------------------------------------------- \n");

		printf("| %s", aux->nombre);
		espacios = 20 - strlen(aux->nombre);
		for(k = 0; k < espacios; k++) printf(" ");

		printf(" | %s", aux->tipo);
		espacios = 30 - strlen(aux->tipo);
		for(k = 0; k < espacios; k++) printf(" ");

		printf(" | %s", aux->evolucionPrevia);
		espacios = 20 - strlen(aux->evolucionPrevia);
		for(k = 0; k < espacios; k++) printf(" ");

		printf(" | %s", aux->evolucionPosterior);
		espacios = 20 - strlen(aux->evolucionPosterior);
		for(k = 0; k < espacios; k++) printf(" ");

		printf(" | %d", aux->numeroPokedex);
		sprintf(num, "%d", aux->numeroPokedex);
		espacios = 20 - strlen(num);
		for(k = 0; k < espacios; k++) printf(" ");

		printf(" | %s", aux->region);
		espacios = 20 - strlen(aux->region);
		for(k = 0; k < espacios; k++) printf(" ");

		printf(" | %d", aux->existencia);
		sprintf(num, "%d", aux->existencia);
		espacios = 10 - strlen(num);
		for(k = 0; k < espacios; k++) printf(" ");

		printf(" |\n ---------------------------------------------------------------------------------------------------------------------------------------------------------------- \n");
	}
	
	// Si no se encuentran Pokemones con el nombre ingresado, se indica que no existe registro
	if(!aux) printf("No existe registro de %s en la Pokedex\n");
	free(aux);
	return;
}