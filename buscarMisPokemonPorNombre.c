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

void buscarMisPokemonPorNombre(Map *MapaPokemon, char nombre[50]){
	if(MapaPokemon == NULL){
		printf("No se tiene registro previo para realizar esta funcion\n\n");
		return;
	}

	bool hayPokemon = false;
	printf("Ingrese nombre de Pokemon: ");
	scanf("%[^\n]s", nombre);
	getchar();

	// Se recorre Mapa Pokemon y se imprimen los Pokemones del almacenamiento del usuario que corresponden al el nombre ingresado
	infoPokemon *aux = (infoPokemon*) firstMap(MapaPokemon);

	printf("Pokemones %s:\n", nombre);
	while(aux != NULL){
		if( strcmp(aux->PokUser->nombre, nombre) == 0){
			printf("%d - %s - %d - %d - %s\n", aux->PokUser->id, aux->PokUser->nombre, aux->PokUser->PC, aux->PokUser->PS, aux->PokUser->sexo);
			hayPokemon = true;
		}
		aux = (infoPokemon*) nextMap(MapaPokemon);

	}

	// Si no se encuentran Pokemones con el nombre ingresado, se indica que no existe registro
	if(hayPokemon == false) printf("No existe registro de pokemon %s en almacenamiento de usuario\n\n", nombre);

	return;
}