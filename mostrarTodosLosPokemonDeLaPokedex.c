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

void mostrarTodosLosPokemonDeLaPokedex(Map *Pokedex_nombre, int totalPokemonPokedex){
	//En caso de entrar a la función sin importar un archivo//
	if(Pokedex_nombre == NULL){
		printf("No se tiene registro previo para realizar esta funcion\n\n");
		return;
	}

	Pokedex *aux = (Pokedex *) firstMap(Pokedex_nombre);
	if(aux == NULL){
		printf("Error en inicializar memoria en variable 'aux' en funcion mostrarTodosLosPokemonDeLaPokedex\n\n");
		exit(1);
	}
		
	printf("Total Pokemon Pokedex: %d\n", totalPokemonPokedex);
	while(aux != NULL){
		printf("%s - %s - %s - %s - %d - %s - %d\n\n", aux->nombre, aux->tipo, aux->evolucionPrevia, aux->evolucionPosterior,
		aux->numeroPokedex, aux->region, aux->existencia);
		
		aux = (Pokedex*) nextMap(Pokedex_nombre);
	}

	free(aux);
	printf("Funcion mostrar finalizada con exito\n\n");
	return;
}