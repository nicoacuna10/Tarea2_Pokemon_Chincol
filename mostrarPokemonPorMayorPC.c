#include <stdio.h>
#include <assert.h>
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

int comparar(const void *a, const void *b){
	int *ptrA = (int *)a;
	int *ptrB = (int *)b;

	return ( *ptrB - *ptrA);
}

void mostrarPokemonPorMayorPC(Map *PokemonUsuario_id, int totalPokemon){
	// Si el mapa no está inicializado, se cierra la función //
	if(PokemonUsuario_id == NULL){
		printf("Por favor importe datos antes de entrar a esta funcion\n\n");
		return;
	}

	int contador = 0;
	int i = 0, k;

	//Luego se crea vector int con números desordenados//
	int *numerosPC = (int *) malloc(totalPokemon * sizeof(int) );
	assert(numerosPC != NULL);
	
	//Se guardan numeros en el vector//
	Pokemon_usuario *aux = (Pokemon_usuario*) firstMap(PokemonUsuario_id);
	for(i = 0; i < totalPokemon; i++){
		numerosPC[i] = aux->PC;
		aux = (Pokemon_usuario*) nextMap(PokemonUsuario_id);
	}

	//Se hace quicksort a numerosPc//
	qsort(numerosPC, totalPokemon, sizeof(int), comparar);

	// Se busca por metodo de fuerza bruta los pokemones que posean el PC segun el vector 'numerosPC'//
	i = 0;
	aux = (Pokemon_usuario *) firstMap(PokemonUsuario_id);
	int espacios;
	char num[7];
	printf(" ----------------------------------------------------------\n");
	printf("| ID  | NOMBRE               | PC     | PS     | SEXO      |\n");
	printf(" ----------------------------------------------------------\n");

	while(contador < totalPokemon){
		if(aux->PC == numerosPC[i]){
			printf("| %d", aux->id);
			sprintf(num, "%d", aux->id);
			espacios = 3 - strlen(num);
			for(k = 0; k < espacios; k++) printf(" ");

			printf(" | %s", aux->nombre);
			espacios = 20 - strlen(aux->nombre);
			for(k = 0; k < espacios; k++) printf(" ");

			printf(" | %d", aux->PC);
			sprintf(num, "%d", aux->PC);
			espacios = 6 - strlen(num);
			for(k = 0; k < espacios; k++) printf(" ");

			printf(" | %d", aux->PS);
			sprintf(num, "%d", aux->PS);
			espacios = 6 - strlen(num);
			for(k = 0; k < espacios; k++) printf(" ");

			printf(" | %s", aux->sexo);
			espacios = 9 - strlen(aux->sexo);
			for(k = 0; k < espacios; k++) printf(" ");
			
			printf(" |\n ----------------------------------------------------------\n");
			i++;
			contador++;
		}
		
		aux = (Pokemon_usuario *) nextMap(PokemonUsuario_id);
		if(aux == NULL) aux =(Pokemon_usuario*) firstMap(PokemonUsuario_id);
	}

	// Se libera memoria del vector dinámico //
	free(numerosPC);
	return;
}