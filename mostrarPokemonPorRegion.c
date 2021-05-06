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
	if(Pokedex_num == NULL){
		printf("No se tiene registro previo para realizar esta funcion\n\n");
		return;
	}

	bool hayPokemonesDeLaRegion = false;
	int contPokemonR = 0;
	char region[20];
	
	printf("Ingrese region: ");
	scanf("%[^\n]s", region);
	getchar();

	// Se recorre MapaPokemon y se va imprimiendo los pokemones que correspondan a la region ingresada
	Pokedex *aux = (Pokedex*) firstMap(Pokedex_num);

	printf("Pokemones de la region %s:\n\n", region);
	while(aux != NULL){
		if( strcmp(aux->region, region) == 0){
			printf("%s - %s - %s - %s - %d - %s\n", aux->nombre, aux->tipo, aux->evolucionPrevia, aux->evolucionPosterior, aux->numeroPokedex, aux->region);
			contPokemonR += aux->existencia;
			hayPokemonesDeLaRegion = true;
		}
		aux = (Pokedex*) nextMap(Pokedex_num);
	}

	if(hayPokemonesDeLaRegion == true) printf("Existen %d pokemones de la region %s\n\n", contPokemonR, region);
	// Si no se encuentra ningun pokemon de la region ingresada, se indica que no existe registro
	if(hayPokemonesDeLaRegion == false) printf("\nNo existen pokemones de la region %s\n\n", region);
	return;
}