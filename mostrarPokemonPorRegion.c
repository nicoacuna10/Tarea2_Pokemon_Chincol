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

void mostrarPokemonPorRegion(Map *Pokedex_num){
	// Si el mapa no está inicializado, se cierra la función //
	if(Pokedex_num == NULL){
		printf("No se tiene registro previo para realizar esta funcion\n\n");
		return;
	}

	// Inicialización de variables //
	bool hayPokemonesDeLaRegion = false;
	int contPokemonR = 0, j = 0, k, espacios;
	char region[20], num[10];
	
	printf("Ingrese region: ");
	scanf("%[^\n]s", region);
	getchar();

	// Se recorre por fuerza bruta la Pokedex y se va imprimiendo los pokemones que correspondan a la region ingresada //
	Pokedex *aux = (Pokedex*) firstMap(Pokedex_num);

	printf("Pokemones de la region %s:\n\n", region);
	while(aux != NULL){
		if( strcmp(aux->region, region) == 0){
			if(j == 0){
				printf(" ---------------------------------------------------------------------------------------------------------------------------------------------------------------- \n");
				printf("| NOMBRE               | TIPO(S)                        | EVOLUCION PREVIA     | EVOLUCION POSTERIOR  | NUMERO POKEDEX       | REGION               | EXISTENCIA |\n");
				printf(" ---------------------------------------------------------------------------------------------------------------------------------------------------------------- \n");
			}
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

			contPokemonR += aux->existencia;
			hayPokemonesDeLaRegion = true;
			j++;
		}
		
		aux = (Pokedex*) nextMap(Pokedex_num);
	}

	// Si se encuentra algún pokemon de la región ingresada, se imprime la cantidad de pokemones de la región // 
	if(hayPokemonesDeLaRegion == true) printf("Existen %d pokemones de la region %s\n\n", contPokemonR, region);
	// Si no se encuentra ningun pokemon de la region ingresada, se indica que no existe registro
	if(hayPokemonesDeLaRegion == false) printf("\nNo existen pokemones de la region %s\n\n", region);
	return;
}