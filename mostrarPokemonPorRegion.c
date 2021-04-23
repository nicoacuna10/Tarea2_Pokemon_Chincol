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

typedef struct{
	Pokemon_usuario* PokUser; 
	Pokedex* Px;
}infoPokemon;

void mostrarPokemonPorRegion(Map *MapaPokemon, char region[20]){
	if(MapaPokemon == NULL){
		printf("No se tiene registro previo para realizar esta funcion\n\n");
		return;
	}

	bool hayPokemonesDeLaRegion = false;
	int contPokemonR = 0;
	printf("Ingrese region: ");
	scanf("%[^\n]s", region);
	getchar();

	// Se recorre MapaPokemon y se va imprimiendo los pokemones que correspondan a la region ingresada
	infoPokemon *aux = (infoPokemon*) firstMap(MapaPokemon);

	printf("Pokemones de la region %s:\n\n", region);
	while(aux != NULL){
		if( strcmp(aux->Px->region, region) == 0){
			printf("%s - %s - %s - %s - %d - %s\n\n", aux->Px->nombre, aux->Px->tipo, aux->Px->evolucionPrevia, aux->Px->evolucionPosterior,
		aux->Px->numeroPokedex, aux->Px->region);
			contPokemonR += aux->Px->existencia;
			hayPokemonesDeLaRegion = true;
		}
		aux = (infoPokemon*) nextMap(MapaPokemon);
	}

	// Si no se encuentra ningun pokemon de la region ingresada, se indica que no existe registro
	if(hayPokemonesDeLaRegion == false) printf("\nNo existen pokemones de la region %s\n", region);
	return;
}