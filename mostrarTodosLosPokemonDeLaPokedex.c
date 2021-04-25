#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Map.h"

typedef struct{
	int id;
	char* nombre;
	float PC;
	float PS;
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

void mostrarTodosLosPokemonDeLaPokedex(Map *MapaPokemon, int totalPokemonPokedex){
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
	printf("Total Pokemon Pokedex: %d\n", totalPokemonPokedex);
	while(aux != NULL){
		if( aux->Px->existencia >= 1 ){
			printf("Numero: %d) - %s - %s - %s - %s - %d - %s - %d\n\n", aux->PokUser->id, aux->Px->nombre, aux->Px->tipo, aux->Px->evolucionPrevia, aux->Px->evolucionPosterior,
			aux->Px->numeroPokedex, aux->Px->region, aux->Px->existencia);
			//Existencia no aparecer por pantalla porque se pierde preliminarmente no se inicializa en cero//
			i++;
		}
		aux = (infoPokemon *) nextMap(MapaPokemon);
	}

	free(aux);
	printf("Funcion mostrar finalizada con exito\n\n");
	return;
}