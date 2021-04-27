#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
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

int cmpFunc(const void *a, const void *b){
	int *ptrA = (int *)a;
	int *ptrB = (int *)b;

	return *ptrB - *ptrA;
}

void mostrarTodosLosPokemonDeLaPokedex(Map *Pokedex_num, int totalPokemonPokedex){
	//En caso de entrar a la función sin importar un archivo//
	if(Pokedex_num == NULL){
		printf("No se tiene registro previo para realizar esta funcion\n\n");
		return;
	}


	//Inicializacion de variables//
	int *numerosOrdenadosDeLaPokedex = (int *) malloc(totalPokemonPokedex * sizeof(int) );
	assert(numerosOrdenadosDeLaPokedex!= NULL);

	Pokedex *aux = (Pokedex *) firstMap(Pokedex_num);
	assert(aux != NULL);

	for(int i = 0; i < totalPokemonPokedex; i++){
		numerosOrdenadosDeLaPokedex[i] = aux->numeroPokedex;
		aux = nextMap(Pokedex_num);	
	}


	qsort(numerosOrdenadosDeLaPokedex, totalPokemonPokedex, sizeof(int), cmpFunc);


	aux = (Pokedex*) firstMap(Pokedex_num);
	int i = 0, contador = 0;
	printf("Total Pokemon Pokedex: %d\n", totalPokemonPokedex);

	while(i < totalPokemonPokedex){
		if(numerosOrdenadosDeLaPokedex[i] == aux->numeroPokedex){
			printf("%d : %s - %s - %s - %s - %d - %s - %d\n\n", i, aux->nombre, aux->tipo, aux->evolucionPrevia, aux->evolucionPosterior,
			aux->numeroPokedex, aux->region, aux->existencia);
			i++;
			if(aux->existencia > 1) contador++;
		}	

		aux = (Pokedex*) nextMap(Pokedex_num);
		if(aux == NULL) aux = (Pokedex*) firstMap(Pokedex_num);
	}
	printf("%d\n", contador);
	free(aux);
	printf("Funcion mostrar finalizada con exito\n\n");
	return;
}