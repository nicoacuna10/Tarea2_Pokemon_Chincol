#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void mostrarTodosLosPokemonDeLaPokedex(Map *MapaPokemon, int totalPokemon){
	//En caso de entrar a la función sin importar un archivo//
	if(MapaPokemon == NULL){
		printf("No se tiene registro previo para realizar esta funcion\n\n");
		return;
	}

	infoPokemon *aux = (infoPokemon *) firstMap(MapaPokemon);
	if(aux == NULL){
		printf("Error en inicializar memoria en variable 'aux' en funcion mostrarTodosLosPokemonDeLaPokedex\n\n");
		exit(1);
	}

	int i = 0;		
	printf("TotalPokemon: %d\n", totalPokemon);
	while(aux != NULL){
		printf("Numero: %d) %s %d %s %s %s %d %s\n\n", aux->Px->numeroPokedex, aux->Px->nombre, aux->Px->existencia, aux->Px->tipo, aux->Px->evolucionPrevia, aux->Px->evolucionPosterior,
		aux->Px->numeroPokedex, aux->Px->region);

		i++;
		aux = (infoPokemon *) nextMap(MapaPokemon);
	}


	free(aux);
	printf("Funcion mostrar finalizada con exito\n\n");
	return;
}