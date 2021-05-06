#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
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


void evolucionarPokemon(Map* PokemonUsuario_id, Map* Pokedex_num, Map* Pokedex_nombre){
	if(PokemonUsuario_id == NULL || Pokedex_nombre == NULL){
		printf("Por favor importe datos antes de entrar a esta funcion\n\n");
		return;
	}

	int id;
	printf("Ingrese id Pokemon: ");
	scanf("%d", &id);
	getchar();

	Pokemon_usuario *aux = (Pokemon_usuario*) searchMap(PokemonUsuario_id, &id);
	if(!aux){
		printf("No existe pokemon con la id %d\n\n", id);
		free(aux);
		return;
	}

	// Testing //
	printf("\n%d | %s | %d | %d | %s\n", aux->id, aux->nombre, aux->PC, aux->PS, aux->sexo);

	Pokedex *aux2 = (Pokedex*) searchMap(Pokedex_nombre, aux->nombre);
	if( strcmp(aux2->evolucionPosterior, "No tiene") == 0){
		printf("El pokemon %s no tiene evolucion posterior\n\n", aux->nombre);
		free(aux);
		free(aux2);
		return;
	}

	aux2->existencia--;
	strcpy(aux->nombre, aux2->evolucionPosterior);
	aux->PC *= 1.5;
	aux->PS *= 1.25;
	Pokedex *aux3 = (Pokedex*) searchMap(Pokedex_nombre, aux2->evolucionPosterior);
	if(aux3 != NULL) aux2->existencia++;
	else{
		strcpy(aux3->nombre, aux2->evolucionPosterior);
		strcpy(aux3->tipo, aux2->tipo);
		strcpy(aux3->evolucionPrevia, aux2->nombre);
		strcpy(aux3->evolucionPosterior, "No tiene\0");
		strcpy(aux3->region, aux2->region);
		aux3->existencia = 1;
		aux3->numeroPokedex = aux2->numeroPokedex;
		insertMap(Pokedex_num, &aux3->numeroPokedex, aux3);
		insertMap(Pokedex_nombre, aux3->nombre, aux3);
	}


	printf("%d - %s - %d - %d - %s\n\n", aux->id, aux->nombre, aux->PC, aux->PS, aux->sexo);
	free(aux);
	free(aux2);
	free(aux3);
	return;
}