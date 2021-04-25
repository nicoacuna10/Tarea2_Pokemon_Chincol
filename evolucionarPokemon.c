#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
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

void buscarMisPokemonPorNombre(Map *MapaPokemon, char nombre[50]);

void evolucionarPokemon(Map* MapaPokemon){
	int id = 0;
	char vectorNombre[50];
	memset(vectorNombre, '\0', 50);

	printf("Ingrese id Pokemon: ");
	scanf("%d", &id);
	getchar();

	infoPokemon *aux = (infoPokemon*) searchMap(MapaPokemon, &id);
	if(aux == NULL){
		printf("No existe pokemon con la id %d\n\n", id);
		free(aux);
		return;
	}

	// Testing //
	printf("\n%d | %s | %d | %d | %s\n", aux->PokUser->id, aux->PokUser->nombre, aux->PokUser->PC, aux->PokUser->PS, aux->PokUser->sexo);

	strcpy(vectorNombre, aux->Px->evolucionPosterior);
	printf("%s\n\n", vectorNombre);

	if( strcmp(vectorNombre, "No tiene") == 0){
		printf("El pokemon %s no tiene evolucion posterior\n\n", aux->PokUser->nombre);
		return;
	}

	infoPokemon *aux2 = (infoPokemon*) firstMap(MapaPokemon);
	assert(aux2 != NULL);

	while(aux2 != NULL){
		if( strcmp(vectorNombre, aux->Px->nombre) == 0){
			//aux->PokUser->PC *= 1.50;  
			//aux->PokUser->PS *= 1.25;
			strcpy(aux->PokUser->nombre,vectorNombre);
			//strcpy(aux->Px->evolucionPosterior, aux2->Px->nombre);
			break;
		}
		aux2 = (infoPokemon*) nextMap(MapaPokemon);
	}
	//free(aux);
	free(aux2);
	return;
}