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

void buscarMisPokemonPorNombre(Map *PokemonUsuario_id){
	if(PokemonUsuario_id == NULL){
		printf("No se tiene registro previo para realizar esta funcion\n\n");
		return;
	}

	bool hayPokemon = false;
	char nombre[50];

	printf("Ingrese nombre de Pokemon: ");
	scanf("%[^\n]s", nombre);
	getchar();

	// Se recorre Mapa Pokemon y se imprimen los Pokemones del almacenamiento del usuario que corresponden con el nombre ingresado
	Pokemon_usuario *aux = (Pokemon_usuario*) firstMap(PokemonUsuario_id);

	printf("Pokemones %s:\n", nombre);
	while(aux != NULL){
		if( strcmp(aux->nombre, nombre) == 0){
			printf("%d - %s - %d - %d - %s\n", aux->id, aux->nombre, aux->PC, aux->PS, aux->sexo);
			hayPokemon = true;
		}
		aux = (Pokemon_usuario*) nextMap(PokemonUsuario_id);

	}

	// Si no se encuentran Pokemones con el nombre ingresado, se indica que no existe registro
	if(hayPokemon == false) printf("No existe registro de pokemon %s en almacenamiento de usuario\n\n", nombre);

	return;
}