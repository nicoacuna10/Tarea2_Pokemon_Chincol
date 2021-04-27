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
	if(PokemonUsuario_id == NULL){
		printf("Por favor importe datos antes de entrar a esta funcion\n\n");
		return;
	}

	int contador = 0;
	int i = 0;

	//Luego se crea vector int con números desordenados//
	int *numerosPC = (int *) malloc(totalPokemon * sizeof(int) );
	assert(numerosPC != NULL);
	
	//Se guardan numeros en el vector//
	Pokemon_usuario *aux = (Pokemon_usuario*) firstMap(PokemonUsuario_id);
	assert(aux != NULL);

	for(i = 0; i < totalPokemon; i++){
		numerosPC[i] = aux->PC;
		aux = (Pokemon_usuario*) nextMap(PokemonUsuario_id);
	}

	//Se hace quicksort a numerosPc//
	qsort(numerosPC, totalPokemon, sizeof(int), comparar);
	i = 0;

	// Se busca por metodo de fuerza bruta los pokemones que posean el PC segun el vector 'numerosPC'//
	aux = (Pokemon_usuario *) firstMap(PokemonUsuario_id);
	while(contador < totalPokemon){
		if(aux->PC == numerosPC[i]){
			printf("%d - %s - %d - %d - %s\n", aux->id, aux->nombre, aux->PC, aux->PS, aux->sexo);
			i++;
			contador++;
		}
		
		aux = (Pokemon_usuario *) nextMap(PokemonUsuario_id);
		if(aux == NULL) aux =(Pokemon_usuario*) firstMap(PokemonUsuario_id);
		//if(i >= totalPokemon) i = 0;
	}

	// OJO SE IMPRIMEN SOLO 92 POKEMONES EN VEZ DE LOS 96//
	return;
}