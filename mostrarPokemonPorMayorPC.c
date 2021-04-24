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

typedef struct{
	Pokemon_usuario* PokUser; 
	Pokedex* Px;
}infoPokemon;

int comparar(const void *a, const void *b){
	int *ptrA = (int *)a;
	int *ptrB = (int *)b;

	return ( *ptrB - *ptrA);
}

void mostrarPokemonPorMayorPC(Map *MapaPokemon){
	if(MapaPokemon == NULL){
		printf("Por favor importe datos antes de entrar a esta funcion\n\n");
		return;
	}

	int totalPokemon = 0;
	int contador = 0;
	int i = 0;
	infoPokemon *aux = (infoPokemon *) firstMap(MapaPokemon);
	assert(aux != NULL);

	//Primero se busca la cantidad de pokemones//
	while(aux != NULL){
		totalPokemon++;
		aux = (infoPokemon *) nextMap(MapaPokemon);
	}

	//Luego se crea vector int con números desordenados//
	int *numerosPC = (int *) malloc(totalPokemon * sizeof(int) );
	assert(numerosPC != NULL);
	
	//Se guardan numeros en el vector//
	aux = (infoPokemon *) firstMap(MapaPokemon);
	assert(aux != NULL);

	for(i = 0; i < totalPokemon; i++){
		numerosPC[i] = aux->PokUser->PC;
		aux = (infoPokemon *) nextMap(MapaPokemon);
	}

	//Se hace quicksort a numerosPc//
	qsort(numerosPC, totalPokemon, sizeof(int), comparar);
	i = 0;

	// Se busca por metodo de fuerza bruta los pokemones que posean el PC segun el vector 'numerosPC'//
	aux = (infoPokemon *) firstMap(MapaPokemon);
	while(contador < totalPokemon){
		if(aux->PokUser->PC == numerosPC[i]){
			printf("%d - %s - %d - %d - %s\n", aux->PokUser->id, aux->PokUser->nombre, aux->PokUser->PC, aux->PokUser->PS,
			aux->PokUser->sexo);
			i++;
			contador++;
		}
		
		aux = (infoPokemon *) nextMap(MapaPokemon);
		if(aux == NULL) aux =(infoPokemon *) firstMap(MapaPokemon);
		//if(i >= totalPokemon) i = 0;
	}

	// OJO SE IMPRIMEN SOLO 92 POKEMONES EN VEZ DE LOS 96//
	return;
}