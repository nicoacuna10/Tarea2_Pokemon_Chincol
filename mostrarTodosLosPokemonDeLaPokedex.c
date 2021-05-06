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

	return *ptrA - *ptrB;
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

	for(int i = 0; i < totalPokemonPokedex; i++){
		numerosOrdenadosDeLaPokedex[i] = aux->numeroPokedex;
		aux = nextMap(Pokedex_num);	
	}


	qsort(numerosOrdenadosDeLaPokedex, totalPokemonPokedex, sizeof(int), cmpFunc);


	aux = (Pokedex*) firstMap(Pokedex_num);
	int i = 0, k, espacios;
	char num[6];

	printf("Total Pokemon Pokedex: %d\n", totalPokemonPokedex);
	printf(" ---------------------------------------------------------------------------------------------------------------------------------------------------------------- \n");
	printf("| NOMBRE               | TIPO(S)                        | EVOLUCION PREVIA     | EVOLUCION POSTERIOR  | NUMERO POKEDEX       | REGION               | EXISTENCIA |\n");
	printf(" ---------------------------------------------------------------------------------------------------------------------------------------------------------------- \n");

	while(i < totalPokemonPokedex){
		if(numerosOrdenadosDeLaPokedex[i] == aux->numeroPokedex){
			printf("| %s", aux->nombre);
			int espacios = 20 - strlen(aux->nombre);
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
			itoa(aux->numeroPokedex, num, 10);
			espacios = 20 - strlen(num);
			for(k = 0; k < espacios; k++) printf(" ");

			printf(" | %s", aux->region);
			espacios = 20 - strlen(aux->region);
			for(k = 0; k < espacios; k++) printf(" ");

			printf(" | %d", aux->existencia);
			itoa(aux->existencia, num, 10);
			espacios = 10 - strlen(num);
			for(k = 0; k < espacios; k++) printf(" ");

			printf(" |\n ---------------------------------------------------------------------------------------------------------------------------------------------------------------- \n");
			i++;
		}
		

		aux = (Pokedex*) nextMap(Pokedex_num);
		if(aux == NULL) aux = (Pokedex*) firstMap(Pokedex_num);
	}
	printf("%d\n", i);
	free(aux);
	printf("Funcion mostrar finalizada con exito\n\n");
	return;
}